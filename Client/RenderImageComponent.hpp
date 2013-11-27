#ifndef _RENDERIMAGECOMPONENT_H_
# define _RENDERIMAGECOMPONENT_H_

#include <string>

#include "ASourceModule.hpp"
#include "ARenderComponent.hpp"
#include "SFMLAnimation.hpp"
#include "APositionComponent.hpp"
#include "ASizeComponent.hpp"
#include "ADataModule.hpp"

class RenderImageComponent : public Engine::ARenderComponent
{
private:
	Engine::ADataModule*					_dataModule;
	Engine::APositionComponent<float, 2>*	_positionComponent;
	Engine::ASizeComponent<2>*				_sizeComponent;
	std::string								_file;
	SFMLImage*								_img;
	Engine::ASourceModule*					_sourceModule;
public:
	RenderImageComponent(std::string const& file);
	RenderImageComponent(RenderImageComponent const& cpy);
	~RenderImageComponent();

	void					initialize();
	void					update();
	void					unload();
	void					draw(Engine::IRender* render);
	Engine::IImage*			getImage() const;
	std::string const		getID() const;
	RenderImageComponent*	clone() const;
};

#endif