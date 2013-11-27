#include "APowerComponent.hpp"

namespace Engine
{
	APowerComponent::APowerComponent(unsigned short power)
		: Engine::AComponent(), _power(power)
	{

	}

	APowerComponent::APowerComponent(APowerComponent const& cpy)
		: Engine::AComponent(cpy), _power(cpy._power)
	{

	}

	APowerComponent::~APowerComponent()
	{

	}

	std::string const	APowerComponent::getFamilyID() const
	{
		return (Engine::AComponent::POWER);
	}

	unsigned short	APowerComponent::getPower() const
	{
		return (this->_power);
	}
	
	void	APowerComponent::setPower(unsigned short power)
	{
		this->_power = power;
	}
}