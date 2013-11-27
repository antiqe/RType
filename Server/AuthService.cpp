
#include "Account.hh"
#include "Value.hpp"
#include "Core.hh"
#include "AuthService.hh"
#include "ChannelConsole.hh"
#include "TCPPacket.hh"

#include "Sleep.hpp"

AuthService::AuthService()
  : _run(false), _state(AuthService::FREE), _log("AuthService")
{
  _log.addChannel(new Logging::ChannelConsole);
  _mfunc[Message::AUTH_AVAILABLE] = &AuthService::onAvailableRequest;
  _mfunc[Message::AUTH_LOGIN] = &AuthService::onLoginRequest;
}

void AuthService::start()
{
  InternalMessage *imsg;

  this->_run = true;
  Logging::Message l("Service is running...", "AuthService", Logging::Message::NOTICE);
  this->_log << l;
  while (this->_run)
    {
      while (!this->_q.isEmpty())
	{
	  imsg = this->_q.pop();
	  APacket *pck = imsg->getPacket();
	  Message *msg = reinterpret_cast<Message *>(pck->getData());
	  (this->*_mfunc[msg->getID()])(imsg->getFromTCP(), msg);
	  /* check delete */
	  delete imsg;
	}
      Ultra::Sleep::usleep(300);
    }
}

void AuthService::notify(InternalMessage *msg)
{
  this->_q.push(msg);
}

void AuthService::stop()
{
  this->_run = false;
}

void AuthService::onLoginRequest(int const to, Message *msg)
{
  std::string login;
  std::string passwd;

  login = msg->getAttr<std::string>(std::string("login"));
  passwd = msg->getAttr<std::string>(std::string("password"));

  Message *rmsg = new Message(Message::AUTH_ACCESS);
  InternalMessage *imsg = new InternalMessage(new TCPPacket(rmsg, 0), to);
  imsg->addReceiver(to);

  Account *acc = Core::acc_manager->getAccount(login);
  if (acc && acc->getPassword() == passwd && acc->getState() == Account::OFFLINE)
    {
      Core::acc_manager->addID(login, to);
      acc->setState(Account::ONLINE);
      rmsg->setAttr("state", Ultra::Value((char)AuthService::ACCEPT));
      Logging::Message l("Authentification for user <" + login + "> successful",
			 "AuthService", Logging::Message::DEBUG);
      this->_log << l;
    }
  else
    {
      rmsg->setAttr("state", Ultra::Value((char)AuthService::REFUSED));
      Logging::Message l("Authentification for user <" + login + "> failure",
			 "AuthService", Logging::Message::DEBUG);
      this->_log << l;
    }

  Core::srv_manager->notifyService(ServiceManager::DISPATCH, imsg);
}

void AuthService::onAvailableRequest(int const to, Message *)
{
  Message *rmsg = new Message(Message::AUTH_AVAILABLE);
  InternalMessage *imsg = new InternalMessage(new TCPPacket(rmsg, 0), to);
  imsg->addReceiver(to);

  rmsg->setAttr("state", Ultra::Value((char)this->_state));
  Core::srv_manager->notifyService(ServiceManager::DISPATCH, imsg);
}

