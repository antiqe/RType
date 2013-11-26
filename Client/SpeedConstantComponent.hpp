#ifndef  _SPEEDCONSTANTCOMPONENT_H_
# define _SPEEDCONSTANTCOMPONENT_H_

#include "ASpeedComponent.hpp"

class SpeedConstantComponent : public Engine::ASpeedComponent
{
public:
	SpeedConstantComponent(float speed = 1.0f);
	SpeedConstantComponent(SpeedConstantComponent const& cpy);
	~SpeedConstantComponent();

	void	initialize();
	void	update();
	void	unload();

	Engine::AComponent*	clone() const;
	std::string const	getID() const;

};

#endif