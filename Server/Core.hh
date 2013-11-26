#ifndef __CORE_HH__
#define __CORE_HH__

#include <vector>

#include "Logger.hpp"
#include "IService.hh"
#include "IDatabase.hh"
#include "AccountManager.hh"
#include "ServiceManager.hh"
#include "RoomManager.hh"
#include "MessageFactory.hpp"

class Core
{
private:

  IDatabase *_db;
  Logging::Logger _log;

public:

  Core();
  bool start();
  
  static AccountManager *acc_manager;
  static ServiceManager *srv_manager;
  static RoomManager	*room_manager;

  static MessageFactory *mfactory;
};

#endif