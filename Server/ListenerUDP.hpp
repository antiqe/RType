
#ifndef __LISTENERUDP_HPP__
#define __LISTENERUDP_HPP__

#include "IListener.hpp"
#include "Logger.hpp"

class ListenerUDP : public IListener
{
private:
  unsigned short	_port;
  unsigned int	_maxClient;
  Logging::Logger	_log;
public:
  ListenerUDP(unsigned short port);
  ~ListenerUDP();
  bool	start();
};

#endif
