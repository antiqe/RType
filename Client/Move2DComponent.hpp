#ifndef  _MOVE2DCOMPONENT_H_
# define _MOVE2DCOMPONENT_H_

#include "AMoveComponent.hpp"
#include "AVectorComponent.hpp"
#include "ASpeedComponent.hpp"
#include "APositionComponent.hpp"

class Move2DComponent : public Engine::AMoveComponent
{
private:
	Engine::AVectorComponent<float, 2>*		_vectorComponent;
	Engine::ASpeedComponent*				_speedComponent;
	Engine::APositionComponent<float, 2>*	_positionComponent;
public:
	Move2DComponent();
	Move2DComponent(Move2DComponent const& cpy);
	~Move2DComponent();

	void				initialize();
	void				update();
	void				unload();

	AComponent			*clone() const;
	std::string const	getID() const;
};


#endif 
