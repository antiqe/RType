
#ifndef __LISTENERTCP_HPP__
#define __LISTENERTCP_HPP__

#include "IListener.hpp"
#include "Logger.hpp"

class ListenerTCP : public IListener
{
private:
  unsigned short	_port;
  unsigned int		_maxClient;
  Logging::Logger	_log;
  
public:
  ListenerTCP(unsigned short port);
  ~ListenerTCP();
  bool	start();
  static void *run(void *listener);
  static void *clientThread(void *client);
};

#endif
