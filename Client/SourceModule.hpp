#ifndef _SOURCEMODULE_H_
# define _SOURCEMODULE_H_

#include "ASourceModule.hpp"
#include "Source.hpp"
#include "SFMLImage.hpp"
#include "SFMLText.hpp"

class SourceModule : public Engine::ASourceModule
{
private:
	Ultra::Source<SFMLImage>		_images;
	Ultra::Source<SFMLText>			_texts;
public:
	SourceModule();
	~SourceModule();

	void	initialize();
	void	update();
	void	unload();

	Engine::IImage*		getImage(std::string const& id);
	Engine::IText*		getText(std::string const& id);
};

#endif