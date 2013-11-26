#include <algorithm>
#include <functional>

#include "IThread.hpp"
#include "ServiceManager.hh"

#ifdef _WIN32
#include "WThread.hpp"
#else
#include "LThread.hpp"
#endif

void ServiceManager::run()
{
  std::for_each(this->_lservice.begin(), this->_lservice.end(), std::bind1st(std::mem_fun(&ServiceManager::runService), this));
}

void ServiceManager::addService(IService *service)
{
  this->_lservice.push_back(service);
}

void ServiceManager::notifyService(unsigned char id_service, InternalMessage *msg)
{
  (this->_lservice[id_service])->notify(msg);
}

bool ServiceManager::runService(IService *service)
{
  Ultra::IThread *thread = 0;
  
#ifdef _WIN32
  thread = new Ultra::WThread();
#else
  thread = new Ultra::LThread();
#endif
  thread->create(&IService::run, service);

  return true;
}
