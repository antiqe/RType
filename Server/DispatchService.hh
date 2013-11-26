#ifndef __DISPATCH_SERVICE_HH__
#define __DISPATCH_SERVICE_HH__

#include "Logger.hpp"

#include "Client.hpp"
#include "InternalMessage.hh"
#include "IService.hh"
#include "SafeQueue.hpp"

class DispatchService : public IService
{
private:
  SafeQueue<InternalMessage *> _q;
  Network::Client _client;
  bool _run;
  Logging::Logger _log;
  typedef void (DispatchService::*DispatchFunc)(InternalMessage *);
  DispatchFunc _tabDisp[3];
public:
  DispatchService();
  virtual void start();
  virtual void stop();
  virtual void notify(InternalMessage *msg);
private:
  void dispatchTCP(InternalMessage *msg);
  void dispatchUDP(InternalMessage *msg);
};

#endif
