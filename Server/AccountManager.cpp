//
// AccountManager.cpp
// 
// Made by Guiho Ronan
// 
// Started on  Sat Oct 26 20:20:09 2013 Guiho Ronan
// Last update Wed Nov  6 12:04:08 2013 titouan boisbras
//

#include "AccountManager.hh"
#include "ChannelConsole.hh"
#include "IResultDatabase.hh"
#include "ScopeLock.hpp"

#ifdef _WIN32
#include "WMutex.hpp"
#else
#include "LMutex.hpp"
#endif

const std::string AccountManager::table = "rt_user";
const std::string AccountManager::field_login = "login";
const std::string AccountManager::field_passwd = "passwd";

AccountManager::AccountManager(IDatabase *db)
  : _db(db), _log("AccountManager")
{
  _log.addChannel(new Logging::ChannelConsole);
#ifdef _WIN32
  _mutex = new Ultra::WMutex();
#else
  _mutex = new Ultra::LMutex();
#endif
}

void AccountManager::run()
{
  this->update();
}

Account *AccountManager::getAccount(std::string const &login)
{
  Ultra::ScopeLock sl(this->_mutex);

  Account *acc = this->_lacc[login];
  if (!acc)
    {
      IResultDatabase *res = this->_db->executeQuery("SELECT * FROM " + AccountManager::table + " WHERE " + AccountManager::field_login + " = \"" + login + "\"");
      if (res && res->next())
	{
	  Account *new_acc = new Account(login, res->getField(AccountManager::field_passwd).as<std::string>());
	  this->_lacc[login] = new_acc;
	  return (new_acc);
	}
      return (0);
    }
  return (acc);
}

Account *AccountManager::getAccount(int const id)
{
  std::string login;
  Ultra::ScopeLock sl(this->_mutex);
  
  if ((login = this->_lid[id]) != "")
    return (this->_lacc[login]);
  return (0);
}

void AccountManager::addID(std::string const &login, int const id)
{
  Ultra::ScopeLock sl(this->_mutex);

  this->_lid[id] = login;
}

void AccountManager::delID(int const id)
{
  Ultra::ScopeLock sl(this->_mutex);

  this->_lid.erase(id);
}

void AccountManager::update()
{
  Ultra::ScopeLock sl(this->_mutex);

  if (this->_db)
    {
      this->_log << Logging::Message("Updating...", "AccountManager", Logging::Message::DEBUG);
      IResultDatabase *res = this->_db->executeQuery("SELECT * FROM " + AccountManager::table);
      while (res && res->next())
	{
	  std::string login = res->getField(AccountManager::field_login).as<std::string>();
	  std::string md5 = res->getField(AccountManager::field_passwd).as<std::string>();
	  this->_lacc[login] = new Account(login, md5);
	}
      Logging::Message msg(Ultra::Value(res->count()).to<unsigned int, std::string>() + " Accounts import from database",
			   "AccountManager", Logging::Message::DEBUG);
      this->_log << msg;
    }
}

void AccountManager::setDatabase(IDatabase *db)
{
  this->_db = db;
}
