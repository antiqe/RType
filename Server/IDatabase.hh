//
// IDatabase.hh
// 
// Made by Guiho Ronan
// 
// Started on  Sat Oct 26 20:19:57 2013 Guiho Ronan
// Last update Sat Oct 26 22:38:23 2013 Guiho Ronan
//

#ifndef __IDATABASE_HH__
#define __IDATABASE_HH__

#include <string>

#include "IResultDatabase.hh"

class IDatabase
{
public:
  virtual bool connect(std::string const &host, unsigned short const port,
		       std::string const &login, std::string const &passwd) = 0;
  virtual IResultDatabase *executeQuery(std::string const &query) = 0;
};

#endif