#include "AShootComponent.hpp"

namespace Engine
{
	AShootComponent::AShootComponent(float max)
		: Engine::AComponent(), _current(0.0f), _max(max < 0.0f ? 0.0f : max)
	{

	}

	AShootComponent::AShootComponent(AShootComponent const& cpy)
		: Engine::AComponent(cpy), _current(cpy._current), _max(cpy._max)
	{

	}

	AShootComponent::~AShootComponent()
	{

	}

	std::string const	AShootComponent::getFamilyID() const
	{
		return (Engine::AComponent::SHOOT);
	}

	float	AShootComponent::getPower() const
	{
		return (this->_current);
	}
}