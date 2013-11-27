#ifndef _SOUNDMODULE_H_
# define _SOUNDMODULE_H_

#include "ASoundModule.hpp"
#include "SourceModule.hpp"

class SoundModule : public Engine::ASoundModule
{
  SourceModule	*_sourceModule;
public:
	SoundModule();
	~SoundModule();

	void	initialize();
	void	update();
	void	unload();
};

#endif

