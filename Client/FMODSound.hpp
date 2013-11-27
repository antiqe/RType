#ifndef __FMODSOUND_H__
# define __FMODSOUND_H__

#include "ISound.hpp"

#include "fmod.hpp"
#include "fmod.h"
#include "fmod_codec.h"
#include "fmod_dsp.h"
#include "fmod_memoryinfo.h"
#include "fmod_errors.h"

class FMODSound : public Engine::ISound
{
private:
  FMOD_SYSTEM	*_system;
  FMOD_SOUND    *_sound;
  FMOD_CHANNEL  *_channel;
  FMOD_BOOL     _tmp;
  std::string   _name;
  Engine::ISound::type	_type;
  int		_frequence;
  float		_volume;

public:

  FMODSound(const std::string &name, const std::string &name_file, Engine::ISound::type type, int frequence);
  virtual ~FMODSound();
  void       	play(void);
  void          stop(void) const;
  void          pause(void);
  bool          isPlaying(void);
  void          volume(float ds);
  void          repeat(void);
  void		reset(void);

  Engine::ISound::type	        getType(void) const;
  int		getFrequence(void) const;
  const std::string &getName(void) const;

  virtual void	initialize();
  virtual void	update();
  virtual void	unload();


  static std::string const	AMBIANCE;
  static std::string const	LASER;

};

#endif
