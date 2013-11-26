#ifndef __SERVICEMANAGER_HH__
#define __SERVICEMANAGER_HH__

#include <vector>

#include "IManager.hh"
#include "IService.hh"

class ServiceManager : public IManager
{
private:
  std::vector<IService *> _lservice;
public:
  
  enum Service
    {
      DISPATCH	= 0,
      AUTH	= 1,
      ROOM	= 2,
      COUNT	= 3
    };

  virtual void run();
  void notifyService(unsigned char id_service, InternalMessage *msg);
  void addService(IService *service);
private:
  bool runService(IService *service);
};

#endif