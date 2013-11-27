#ifndef _RENDERANIMATIONCOMPONENT_H_
# define _RENDERANIMATIONCOMPONENT_H_

#include <string>

#include "ASourceModule.hpp"
#include "ARenderComponent.hpp"
#include "SFMLAnimation.hpp"
#include "APositionComponent.hpp"
#include "ASizeComponent.hpp"
#include "ADataModule.hpp"

class RenderAnimationComponent : public Engine::ARenderComponent
{
private:
	Engine::ADataModule*					_dataModule;
	Engine::APositionComponent<float, 2>*	_positionComponent;
	Engine::ASizeComponent<2>*				_sizeComponent;
	std::string								_file;
	SFMLAnimation*							_animation;
	Engine::ASourceModule*					_sourceModule;
	SFMLAnimation::ContextIterator			_context;
public:
	RenderAnimationComponent(std::string const& file);
	RenderAnimationComponent(RenderAnimationComponent const& cpy);
	~RenderAnimationComponent();

	void						initialize();
	void						update();
	void						unload();
	void						draw(Engine::IRender* render);
	Engine::IImage*				getImage() const;
	std::string const			getID() const;
	RenderAnimationComponent*	clone() const;
};

#endif