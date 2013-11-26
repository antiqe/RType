#ifndef __CONFIGURATION_H__
#define __CONFIGURATION_H__

#include "INIReader.hpp"
#include "INISection.hpp"

class	Configuration
{
private:
  Ultra::INIReader		_conf;

public:
  static int				X;
  static int				Y;
  static float				SCALE;
  static unsigned long		MODE;
  static std::string const	NAME;

  Configuration(std::string const &filename);
  ~Configuration();

  void	initialize();
};

#endif // __CONFIGURATION_HPP__
