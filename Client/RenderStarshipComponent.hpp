#ifndef _RENDERSTARSHIPCOMPONENT_H_
# define _RENDERSTARSHIPCOMPONENT_H_

#include <string>

#include "ASourceModule.hpp"
#include "ARenderComponent.hpp"
#include "SFMLAnimation.hpp"
#include "APositionComponent.hpp"
#include "ASizeComponent.hpp"
#include "AVectorComponent.hpp"
#include "ADataModule.hpp"

class RenderStarshipComponent : public Engine::ARenderComponent
{
private:
	enum Status
	{
		UP = 0,
		DOWN,
		NORMAL,
		STATUSSIZE
	};
	RenderStarshipComponent::Status			_current;
	Engine::ADataModule*					_dataModule;
	Engine::AVectorComponent<float, 2>*		_vectorComponent;
	Engine::APositionComponent<float, 2>*	_positionComponent;
	Engine::ASizeComponent<2>*				_sizeComponent;
	Engine::ASourceModule*					_sourceModule;
	std::string								_file[RenderStarshipComponent::STATUSSIZE];
	SFMLImage*								_img[RenderStarshipComponent::STATUSSIZE];
public:
	RenderStarshipComponent(std::string const& normal, std::string const& up, std::string const& down);
	RenderStarshipComponent(RenderStarshipComponent const& cpy);
	~RenderStarshipComponent();

	void						initialize();
	void						update();
	void						unload();
	void						draw(Engine::IRender* render);
	Engine::IImage*				getImage() const;
	std::string const			getID() const;
	RenderStarshipComponent*	clone() const;
};

#endif