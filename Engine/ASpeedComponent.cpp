#include "ASpeedComponent.hpp"

namespace Engine
{
	ASpeedComponent::ASpeedComponent(float speed)
		: Engine::AComponent(), _speed(speed)
	{

	}

	ASpeedComponent::ASpeedComponent(ASpeedComponent const& cpy)
		: Engine::AComponent(cpy), _speed(cpy._speed)
	{

	}

	ASpeedComponent::~ASpeedComponent()
	{

	}

	std::string const	ASpeedComponent::getFamilyID() const
	{
		return (Engine::AComponent::SPEED);
	}

	float	ASpeedComponent::getSpeed() const
	{
		return (this->_speed);
	}

	void	ASpeedComponent::setSpeed(float speed)
	{
		this->_speed = speed;
	}
}
