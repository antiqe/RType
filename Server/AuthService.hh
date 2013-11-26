#ifndef __AUTH_SERVICE_HH__
#define __AUTH_SERVICE_HH__

#include "Logger.hpp"

#include "Message.hpp"
#include "InternalMessage.hh"
#include "IService.hh"
#include "SafeQueue.hpp"

class AuthService : public IService
{
private:

  enum StateService
    {
      BUSY = 1,
      MAINTENANCE = 2,
      FREE = 2,
      OVERLOAD = 3
    };

  enum StateAccount
    {
      ACCEPT = 1,
      REFUSED = 2,
      BAN = 3
    };

  bool _run;
  typedef void (AuthService::*MsgFunc)(int const to, Message *msg);
  MsgFunc _mfunc[Message::COUNT];
  SafeQueue<InternalMessage *> _q;
  AuthService::StateService _state;
  Logging::Logger _log;

public:
  AuthService();
  virtual void start();
  virtual void stop();
  virtual void notify(InternalMessage *msg);
private:
  void onAvailableRequest(int const to, Message *msg);
  void onLoginRequest(int const to, Message *msg);
};

#endif
