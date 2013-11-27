#include <list>
#include <algorithm>
#include <functional>

#include "InternalMessage.hh"
#include "DispatchService.hh"
#include "ChannelConsole.hh"

#include "Sleep.hpp"

DispatchService::DispatchService()
  : _client("", 0), _run(false), _log("DispatchService")
{
  _log.addChannel(new Logging::ChannelConsole);
  _tabDisp[1] = &DispatchService::dispatchTCP;
  _tabDisp[2] = &DispatchService::dispatchUDP;
  _client.connect(ISocket::UDP);
}

void DispatchService::start()
{
  InternalMessage *msg;

  this->_run = true;

  Logging::Message l("Service is running...", "DispatchService", Logging::Message::NOTICE);
  this->_log << l;

  while (this->_run)
    {
      while (!this->_q.isEmpty())
	{
	  msg = this->_q.pop();
	  (this->*_tabDisp[msg->getProto()])(msg);
	  /* check delete */
	  //delete msg;
	}
      Ultra::Sleep::usleep(300);
    }
}

void DispatchService::notify(InternalMessage *msg)
{
  this->_q.push(msg);
}

void DispatchService::stop()
{
  this->_run = false;
}

#include "Message.hpp"

void DispatchService::dispatchTCP(InternalMessage *imsg)
{
  char *buffer;
  unsigned short length;
  std::list<int> lto = imsg->getReceiversTCP();

  for (std::list<int>::iterator it = lto.begin(); it != lto.end(); ++it)
    {
      APacket *pck = imsg->getPacket();
      buffer = pck->pack(length);

      this->_client.setSocket(*it);
      this->_client.send(buffer, length, ISocket::TCP);
    }
}

void DispatchService::dispatchUDP(InternalMessage *msg)
{
  std::list<struct sockaddr_in> lto = msg->getReceiversUDP();

  for (std::list<struct sockaddr_in>::iterator it = lto.begin(); it != lto.end(); ++it)
    {
      this->_client.setSockaddr(*it);
      this->_client.setSockaddrSize(sizeof(*it));

    }
}
