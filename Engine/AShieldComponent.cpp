#include "AShieldComponent.hpp"

namespace Engine
{
	AShieldComponent::AShieldComponent(unsigned int shield)
		: Engine::AComponent(), _shield(shield)
	{

	}

	AShieldComponent::AShieldComponent(AShieldComponent const& cpy)
		: Engine::AComponent(cpy), _shield(cpy._shield)
	{

	}

	AShieldComponent::~AShieldComponent()
	{

	}

	std::string const	AShieldComponent::getFamilyID() const
	{
		return (Engine::AComponent::SHIELD);
	}

	unsigned int	AShieldComponent::getShield() const
	{
		return (this->_shield);
	}

	void	AShieldComponent::setShield(unsigned int shield)
	{
		this->_shield = shield;
	}

	bool	AShieldComponent::isActive() const
	{
		return (this->_shield ? true : false);
	}
}