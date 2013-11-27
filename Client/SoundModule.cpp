#include "SoundModule.hpp"
#include "FMODSound.hpp"

SoundModule::SoundModule()
  : _sourceModule(0)
{
}

SoundModule::~SoundModule(){}

void	SoundModule::initialize()
{
  if (this->_owner)
    {
      if ((this->_sourceModule = dynamic_cast<SourceModule*>(this->_owner->getModule(Engine::AModule::SOURCE))))
	{
	  this->addSound(FMODSound::AMBIANCE, this->_sourceModule->getSound(FMODSound::AMBIANCE));
	  this->addSound(FMODSound::LASER, this->_sourceModule->getSound(FMODSound::LASER));
	}
    }
}

void	SoundModule::update()
{
   this->manageSounds();
}

void	SoundModule::unload(){}
