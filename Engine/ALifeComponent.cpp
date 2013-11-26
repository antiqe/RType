#include "ALifeComponent.hpp"

namespace Engine
{
	ALifeComponent::ALifeComponent(unsigned int max)
		: Engine::AComponent(), _current(max), _max(max)
	{

	}

	ALifeComponent::ALifeComponent(unsigned int current, unsigned int max)
		: Engine::AComponent(), _current(0), _max(max)
	{
		this->setCurrentLife(current);
	}

	ALifeComponent::ALifeComponent(ALifeComponent const& cpy)
		: Engine::AComponent(cpy), _current(cpy._current), _max(cpy._max)
	{

	}

	ALifeComponent::~ALifeComponent()
	{

	}

	std::string const	ALifeComponent::getFamilyID() const
	{
		return (Engine::AComponent::LIFE);
	}

	unsigned int	ALifeComponent::getCurrentLife() const
	{
		return (this->_current);
	}

	unsigned int	ALifeComponent::getMaxLife() const
	{
		return (this->_max);
	}

	void	ALifeComponent::setCurrentLife(unsigned int life)
	{
		this->_current = life > this->_max ? this->_max : ((int)life < 0 ? 0 : life);
	}
}