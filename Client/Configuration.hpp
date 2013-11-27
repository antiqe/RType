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
  static int				GLOBAL_SOUND;
  static int				AMBIENT_SOUND;
  static int				EFFECT_SOUND;
  static int				UP;
  static int				DOWN;
  static int				LEFT;
  static int				RIGHT;
  static int				SHOOT;

  Configuration(std::string const &filename);
  ~Configuration();

  void	initialize();
};

#endif // __CONFIGURATION_HPP__
