//
// MySQLDatabase.cpp
// 
// Made by Guiho Ronan
// 
// Started on  Sat Oct 26 21:27:39 2013 Guiho Ronan
// Last update Wed Nov  6 11:59:17 2013 titouan boisbras
//

#include <vector>
#include <string>

#include "MySQLDatabase.hh"
#include "MySQLResultDatabase.hh"

#include "mysql.h"

MySQLDatabase::MySQLDatabase(std::string const &name)
  : _name(name), _isconnect(false), _con(0)
{

}

bool MySQLDatabase::isConnected() const
{
  return (this->_isconnect);
}

std::string MySQLDatabase::getNameDatabase() const
{
  return (this->_name);
}

bool MySQLDatabase::connect(std::string const &host, unsigned short const port,
			    std::string const &login, std::string const &passwd)
{
  if ((this->_con = mysql_init(0)) == 0)
    {
      this->_isconnect = false;
      return (false);
    }
  if (mysql_real_connect(this->_con, host.c_str(), login.c_str(), passwd.c_str(), 
			 this->_name.c_str(), port, 0, 0) == 0) 
    {
      this->_isconnect = false;
      return (false);
    }  
  this->_isconnect = true;
  return (true);
}

IResultDatabase *MySQLDatabase::executeQuery(std::string const &query)
{
  if (this->_isconnect)
    {
      MYSQL_ROW row;
      MYSQL_RES *res = 0;
      unsigned int count_fields = 0;
      std::vector<std::string> field_name;
      MYSQL_FIELD *field = 0;
      MySQLResultDatabase *mres = new MySQLResultDatabase();
      
      if (mysql_query(this->_con, query.c_str())) 
	return (0);
      if ((res = mysql_store_result(this->_con)) == 0)
	return (0);
      count_fields = mysql_num_fields(res);
      for (unsigned int i = 0; i < count_fields; ++i)
	{
	  field = mysql_fetch_field(res);
	  field_name.push_back(field->name);
	}
      unsigned int total = 0;
      while ((row = mysql_fetch_row(res)))
	{
	  for (unsigned int i = 0; i < count_fields; ++i)
	    {
	      Ultra::Value val(std::string(const_cast<char *>(row[i])));
	      mres->setField(field_name[i], val);
	      mres->next();
	    }
	  total++;
	}
      mres->setCount(total);
      mysql_free_result(res);
      mres->reset();
      return (mres);
    }
  return (0);
}
