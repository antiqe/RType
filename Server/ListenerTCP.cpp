#include <cstring>

#include "Core.hh"
#include "IThread.hpp"
#include "IPacket.hpp"
#include "TCPPacket.hh"
#include "Value.hpp"
#include "ListenerTCP.hpp"
#include "Client.hpp"
#include "Server.hpp"
#include "ChannelConsole.hh"
#include "InternalMessage.hh"
#include "Aggregator.hpp"

#include "Message.hpp"

#ifdef _WIN32
#include "WThread.hpp"
#else
#include "LThread.hpp"
#endif

#include "BinaryStream.hpp"

ListenerTCP::ListenerTCP(unsigned short port)
  : _port(port), _maxClient(99999), _log("ListenerTCP")
{
  _log.addChannel(new Logging::ChannelConsole);
}

ListenerTCP::~ListenerTCP()
{
}

bool	ListenerTCP::start()
{
  Network::Server	server(_port);

  Logging::Message msg("Start TCP listening on port : " + Ultra::Value(_port).to<unsigned short, std::string>()
		       + "...", "LTCP", Logging::Message::NOTICE);
  this->_log << msg;
  if (!server.run(_maxClient, ISocket::TCP))
    {
      Logging::Message msg("Failed to start", "LTCP", Logging::Message::_ERROR);
      this->_log << msg;
      return false;
    }

  while (1)
    {
      Ultra::IThread *cthread = 0;

      Network::Client	*client = server.acceptConnection();

      Logging::Message msg("Incoming connection from " + client->getHost(), "LTCP", Logging::Message::DEBUG);
      this->_log << msg;

      #ifdef _WIN32
      cthread = new Ultra::WThread();
      #else
      cthread = new Ultra::LThread();
      #endif

      cthread->create(&ListenerTCP::clientThread, client);

     }
  return true;
}

void *ListenerTCP::run(void *listener)
{
  ListenerTCP *ltcp = reinterpret_cast<ListenerTCP *>(listener);

  if (ltcp)
    ltcp->start();
  return (0);
}

void *ListenerTCP::clientThread(void *param)
{
  int ret;
  int sock;
  char buffer[1024];
  Network::Client *client;
  Aggregator	agg;

  client = reinterpret_cast<Network::Client *>(param);
  Logging::Logger log("Thread:" + client->getHost());
  log.addChannel(new Logging::ChannelConsole);
  sock = client->getSocket();
  if (client)
    {
      APacket *packet = new TCPPacket();
      while (true)
	{
	  if ((ret = client->receive(buffer, 1024)) <= 0)
	    {
	      Account *acc = Core::acc_manager->getAccount(sock);
	      if (acc)
		{
		  acc->setState(Account::OFFLINE);
		  Core::acc_manager->delID(client->getSocket(ISocket::TCP));
		}
	      client->disconnect();
	      Logging::Message l("Client disconnected " + client->getHost(), "LTCP", Logging::Message::DEBUG);
	      log << l;
	      return (0);
	    }
	  agg.integrity(ret, buffer, packet);
	  while (!agg.isEmpty())
	    {
	      packet->unpack(agg.getMsgFront().first, agg.getMsgFront().second);
	      agg.popMsg();

	      if (packet->getService() > ServiceManager::DISPATCH && packet->getService() < ServiceManager::COUNT)
		Core::srv_manager->notifyService(packet->getService(),
						 new InternalMessage(packet, client->getSocket()));
	    }
	}
    }
  return (0);
}
