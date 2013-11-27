
#include	"FMODSound.hpp"

std::string const	FMODSound::AMBIANCE = "ambiance";
std::string const	FMODSound::LASER = "laser";


FMODSound::FMODSound(const std::string &name, const std::string &name_file, Engine::ISound::type type, int frequence)
  : _tmp(false), _name(name), _type(type), _frequence(frequence), _volume(1.0)
{
  FMOD_System_Create(&(this->_system));
  FMOD_System_Init(this->_system, 1, FMOD_INIT_NORMAL, NULL);
  FMOD_System_CreateSound(this->_system, name_file.c_str(),
			  FMOD_CREATESAMPLE, 0, &(this->_sound));
}

FMODSound::~FMODSound()
{
  FMOD_System_Close(this->_system);
  FMOD_System_Release(this->_system);
}

void        FMODSound::play(void)
{
  if (this->_channel)
    {
      FMOD_Channel_GetPaused(this->_channel, &(this->_tmp));
    }
  if (this->_tmp == true)
    FMOD_Channel_SetPaused(this->_channel, false);
  else
    FMOD_System_PlaySound(this->_system, FMOD_CHANNEL_FREE,
			  this->_sound, 0, &(this->_channel));
  FMOD_Channel_SetVolume(this->_channel, this->_volume);
}

void        FMODSound::stop(void) const
{
  FMOD_Channel_SetPaused(this->_channel, true);
}

void        FMODSound::pause(void)
{
  FMOD_Channel_GetPaused(this->_channel, &(this->_tmp));
  if (this->_tmp == false)
    FMOD_Channel_SetPaused(this->_channel, true);
}

bool        FMODSound::isPlaying(void)
{
  FMOD_Channel_IsPlaying(this->_channel, &(this->_tmp));
  return this->_tmp;
}

void        FMODSound::volume(float ds)
{
  this->_volume = ds;
}

void        FMODSound::repeat(void)
{
  FMOD_System_PlaySound(this->_system, FMOD_CHANNEL_FREE,
			this->_sound, 0, &(this->_channel));
}

void		FMODSound::reset(void)
{
  if (this->isPlaying() == false)
    this->play();
  else
    {
      this->stop();
      this->play();
    }
}

Engine::ISound::type   FMODSound::getType(void) const
{
  return this->_type;
}

int		FMODSound::getFrequence(void) const
{
  return this->_frequence;
}

const std::string &FMODSound::getName(void) const
{
  return this->_name;
}

void	FMODSound::initialize()
{
}

void	FMODSound::update()
{
}

void	FMODSound::unload()
{
}
