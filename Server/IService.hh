#ifndef __ISERVICE_HH__
#define __ISERVICE_HH__

#include "InternalMessage.hh"

class IService
{
public:
  virtual void start() = 0;
  virtual void stop() = 0;
  virtual void notify(InternalMessage *msg) = 0;
  static void *run(void *param)
  {
    IService *service = reinterpret_cast<IService *>(param);
    if (service)
      service->start();
    return 0;
  }
};

#endif
