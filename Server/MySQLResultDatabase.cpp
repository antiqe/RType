//
// MySQLResultDatabase.cpp
// 
// Made by Guiho Ronan
// 
// Started on  Sat Oct 26 23:31:06 2013 Guiho Ronan
// Last update Sun Oct 27 00:16:55 2013 Guiho Ronan
//

#include "MySQLResultDatabase.hh"

MySQLResultDatabase::MySQLResultDatabase()
  : _indice(-1), _count(0)
{ }

void MySQLResultDatabase::reset()
{
  this->_indice = -1;
}

bool MySQLResultDatabase::next()
{
  return (++this->_indice < this->_count ? true : false);
}

unsigned int MySQLResultDatabase::count() const
{
  return (this->_count);
}

Ultra::Value MySQLResultDatabase::getField(std::string const &name)
{
  return (this->_fields[name][this->_indice]);
}

void MySQLResultDatabase::setField(std::string const &name, Ultra::Value &val)
{
  this->_fields[name].push_back(val);
}

void MySQLResultDatabase::setCount(unsigned int const val)
{
  this->_count = val;
}
