//
// MySQLDatabase.hh
// 
// Made by Guiho Ronan
// 
// Started on  Sat Oct 26 21:12:32 2013 Guiho Ronan
// Last update Sat Oct 26 22:20:32 2013 Guiho Ronan
//

#ifndef __MMYSQLDATABASE_HH__
#define __MMYSQLDATABASE_HH__

#include <string>

#include "IDatabase.hh"

#include "mysql.h"

class MySQLDatabase : public IDatabase
{
private:
  std::string _name;
  bool _isconnect;
  MYSQL *_con;
public:
  MySQLDatabase(std::string const &name);
  bool isConnected() const;
  std::string getNameDatabase() const;
  virtual bool connect(std::string const &host, unsigned short const port,
		       std::string const &login, std::string const &passwd);
  virtual IResultDatabase *executeQuery(std::string const &query);
};

#endif
