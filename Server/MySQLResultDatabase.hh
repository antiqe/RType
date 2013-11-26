//
// MySQLResultDatabase.hh
// 
// Made by Guiho Ronan
// 
// Started on  Sat Oct 26 23:27:19 2013 Guiho Ronan
// Last update Sun Oct 27 00:17:13 2013 Guiho Ronan
//

#ifndef __MYSQLRESULTDATABASE_HH__
#define __MYSQLRESULTDATABASE_HH__

#include <map>
#include <vector>
#include <string>

#include "Value.hpp"
#include "IResultDatabase.hh"

class MySQLResultDatabase : public IResultDatabase
{
private:
  int _indice;
  std::map<std::string, std::vector<Ultra::Value> > _fields;
  int _count;
public:
  MySQLResultDatabase();
  virtual void reset();
  virtual bool next();
  virtual unsigned int count() const;
  virtual Ultra::Value getField(std::string const &name);
  void setCount(unsigned int const val);
  void setField(std::string const &name, Ultra::Value &val);
};

#endif