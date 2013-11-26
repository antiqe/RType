#include "AInvincibilityComponent.hpp"

namespace Engine
{
	AInvincibilityComponent::AInvincibilityComponent()
		: Engine::AComponent(), _active(false)
	{

	}

	AInvincibilityComponent::AInvincibilityComponent(AInvincibilityComponent const& cpy)
		: Engine::AComponent(cpy), _active(cpy._active)
	{

	}

	AInvincibilityComponent::~AInvincibilityComponent()
	{

	}

	std::string const	AInvincibilityComponent::getFamilyID() const
	{
		return (Engine::AComponent::INVINCIBILITY);
	}

	bool	AInvincibilityComponent::active() const
	{
		return (this->_active);
	}
}