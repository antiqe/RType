#include	"SpeedConstantComponent.hpp"

SpeedConstantComponent::SpeedConstantComponent(SpeedConstantComponent const& cpy)
	: Engine::ASpeedComponent(cpy)
{
	_speed = cpy.getSpeed();
}

SpeedConstantComponent::SpeedConstantComponent(float speed)
	: Engine::ASpeedComponent(speed)
{

}

SpeedConstantComponent::~SpeedConstantComponent()
{

}

void	SpeedConstantComponent::initialize()
{

}

void	SpeedConstantComponent::update()
{

}

void	SpeedConstantComponent::unload()
{

}

Engine::AComponent  *SpeedConstantComponent::clone() const
{
	return (new SpeedConstantComponent(*this));
}

std::string const	SpeedConstantComponent::getID() const
{
	return ("speedConstant");
}

