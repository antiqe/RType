//
// AccountManager.hh
// 
// Made by Guiho Ronan
// 
// Started on  Sat Oct 26 20:20:17 2013 Guiho Ronan
// Last update Sat Oct 26 20:31:26 2013 Guiho Ronan
//

#ifndef __ACCOUNT_MANAGER_HH__
#define __ACCOUNT_MANAGER_HH__

#include <string>
#include <vector>

#include "Account.hh"
#include "IManager.hh"
#include "IDatabase.hh"
#include "IMutex.hpp"

#include "Logger.hpp"

class AccountManager : public IManager
{
private:
  IDatabase *_db;
  std::map<int, std::string> _lid;
  std::map<std::string, Account *> _lacc;
  Logging::Logger _log;
  Ultra::IMutex *_mutex;

  static const std::string table;
  static const std::string field_login;
  static const std::string field_passwd;

public:
  AccountManager(IDatabase *db);
  virtual void run();
  void setDatabase(IDatabase *db);

  Account *getAccount(std::string const &login);
  Account *getAccount(int const id);

  void addID(std::string const &login, int const id);
  void delID(int const id);

  void update();
};

#endif