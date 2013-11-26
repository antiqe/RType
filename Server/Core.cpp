#include <algorithm>
#include <functional>

#include "Core.hh"
#include "IThread.hpp"
#include "ChannelConsole.hh"
#include "ListenerUDP.hpp"
#include "ListenerTCP.hpp"

#include "AuthService.hh"
#include "RoomService.hh"
#include "DispatchService.hh"

#include "MySQLDatabase.hh"

#include "AccountManager.hh"
#include "ServiceManager.hh"
#include "Configuration.hpp"

#ifdef _WIN32
#include "WThread.hpp"
#else
#include "LThread.hpp"
#endif

AccountManager* Core::acc_manager = new AccountManager(0);
ServiceManager* Core::srv_manager = new ServiceManager();
RoomManager*	Core::room_manager = new RoomManager();

MessageFactory *Core::mfactory = new MessageFactory();

Core::Core()
  : _db(0), _log("Core")
{
  _log.addChannel(new Logging::ChannelConsole);
  Core::srv_manager->addService(new DispatchService);
  Core::srv_manager->addService(new AuthService);
  Core::srv_manager->addService(new RoomService);
  Configuration	conf("config.ini");
  conf.initialize();
}

bool Core::start()
{

  this->_db = new MySQLDatabase(Configuration::DATABASE_DATABASE);

  Logging::Message l("Connection to database " + Configuration::DATABASE_DATABASE + "@" + Configuration::DATABASE_HOST + " ...", "Core", Logging::Message::NOTICE);
  this->_log << l;
  if (!this->_db->connect(Configuration::DATABASE_HOST, Configuration::DATABASE_PORT, Configuration::DATABASE_LOGIN, Configuration::DATABASE_PASSWORD))
    {
      Logging::Message l("Connection to database failed", "Core", Logging::Message::_ERROR);
      this->_log << l;
      return false;
    }
  Logging::Message ls("Connection to database success", "Core", Logging::Message::NOTICE);
  this->_log << ls;

  Core::acc_manager->setDatabase(this->_db);
  Core::acc_manager->run();

  Core::srv_manager->run();

  Ultra::IThread *thread_tcp = 0;
#ifdef _WIN32
  thread_tcp = new Ultra::WThread();
#else
  thread_tcp = new Ultra::LThread();
#endif

  ListenerTCP *ltcp = new ListenerTCP(Configuration::TCP_PORT);
  thread_tcp->create(&ListenerTCP::run, ltcp);

  ListenerUDP ludp(Configuration::UDP_PORT);
  ludp.start();

  return true;
}

