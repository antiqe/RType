//
// Configuration.cpp for  in /home/boisbr_t//project/rtype/Server
// 
// Made by titouan boisbras
// Login   <boisbr_t@epitech.net>
// 
// Started on  Wed Nov 20 10:41:45 2013 titouan boisbras
// Last update Wed Nov 20 17:42:29 2013 titouan boisbras
//

#include "Configuration.hpp"

unsigned short   Configuration::UDP_PORT = 8080;
unsigned short   Configuration::TCP_PORT = 8081;
unsigned short   Configuration::DATABASE_PORT = 3306;
std::string      Configuration::DATABASE_HOST  = "88.191.133.132";
std::string      Configuration::DATABASE_LOGIN = "rtype";
std::string      Configuration::DATABASE_PASSWORD = "rtype35";
std::string      Configuration::DATABASE_DATABASE = "rtype";

Configuration::Configuration(std::string const &filename)
	: _conf(filename)
{

}

Configuration::~Configuration()
{

}

void	Configuration::initialize()
{
	if (this->_conf.load())
	{
		Ultra::INISection	*section;
		if ((section = this->_conf.getSection("global")))
		{
			Configuration::UDP_PORT = section->getField<unsigned short>("udp_port");
			Configuration::TCP_PORT = section->getField<unsigned short>("tcp_port");
		}
		if ((section = this->_conf.getSection("database")))
		{
			Configuration::DATABASE_HOST = section->getField<std::string>("host");
			Configuration::DATABASE_PORT = section->getField<unsigned short>("port");
			Configuration::DATABASE_LOGIN = section->getField<std::string>("login");
			Configuration::DATABASE_PASSWORD = section->getField<std::string>("password");
			Configuration::DATABASE_DATABASE = section->getField<std::string>("database");
		}
	}
}
