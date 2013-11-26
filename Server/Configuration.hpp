//
// Configuration.hpp for  in /home/boisbr_t//project/rtype/Server
// 
// Made by titouan boisbras
// Login   <boisbr_t@epitech.net>
// 
// Started on  Wed Nov 20 10:44:27 2013 titouan boisbras
// Last update Wed Nov 20 14:19:42 2013 titouan boisbras
//

#ifndef __CONFIGURATION_HPP__
#define __CONFIGURATION_HPP__

#include "INIReader.hpp"
#include "INISection.hpp"

class	Configuration
{
private:
  Ultra::INIReader		_conf;

public:
  static unsigned short	UDP_PORT;
  static unsigned short	TCP_PORT;
  static std::string	DATABASE_HOST;
  static unsigned short	DATABASE_PORT;
  static std::string	DATABASE_LOGIN;
  static std::string	DATABASE_PASSWORD;
  static std::string	DATABASE_DATABASE;

  Configuration(std::string const &filename);
  ~Configuration();

  void	initialize();
};

#endif // __CONFIGURATION_HPP__
