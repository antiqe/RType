//
// IResultDatabase.hh
// 
// Made by Guiho Ronan
// 
// Started on  Sat Oct 26 21:19:21 2013 Guiho Ronan
// Last update Sat Oct 26 23:37:21 2013 Guiho Ronan
//

#ifndef __IRESULTDATABASE_HH__
#define __IRESULTDATABASE_HH__

#include "Value.hpp"

class IResultDatabase
{
public:
  virtual void reset() = 0;
  virtual bool next() = 0;
  virtual unsigned int count() const = 0;
  virtual Ultra::Value getField(std::string const &name) = 0;
};

#endif