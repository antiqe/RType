#include <cstring>

#include "Room.hh"
#include "Core.hh"
#include "Client.hpp"
#include "ChannelConsole.hh"
#include "ListenerUDP.hpp"
#include "Client.hpp"
#include "Server.hpp"
#include "Value.hpp"
#include "IPacket.hh"
#include "UDPPacket.hh"

ListenerUDP::ListenerUDP(unsigned short port)
  : _port(port), _maxClient(99999), _log("ListenerUDP")
{
  _log.addChannel(new Logging::ChannelConsole);
}

ListenerUDP::~ListenerUDP()
{
}

bool	ListenerUDP::start()
{
  int  ret;
  char buffer[1024];
  Network::Client	client("", 0);
  Network::Server	server(_port);

  Logging::Message msg("Start UDP listening on port : " + Ultra::Value(_port).to<unsigned short, std::string>()
		       + "...", "LUDP", Logging::Message::NOTICE);
  this->_log << msg;
  
  if (!server.run(_maxClient, ISocket::UDP))
    {
      Logging::Message msg("Failed to start", "LUDP", Logging::Message::_ERROR);
      this->_log << msg;
      return false;
    }
  
  client.setSocket(server.getSocket(ISocket::UDP), ISocket::UDP);
  UDPPacket *packet = new UDPPacket();

  while (true)
    {
      if ((ret = client.receive(buffer, 1024, ISocket::UDP)) > 0)
		{
			if (packet->unpack(buffer, ret))
			{
				if (packet->getService() > ServiceManager::DISPATCH && packet->getService() < ServiceManager::COUNT)
					Core::srv_manager->notifyService(packet->getService(),
													new InternalMessage(packet, client.getSockaddr()));
			}
		}
    }
  return true;
}
