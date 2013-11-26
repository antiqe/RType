#include "ACollidorComponent.hpp"

namespace Engine
{
	ACollidorComponent::ACollidorComponent()
		: Engine::AComponent()
	{

	}

	ACollidorComponent::ACollidorComponent(ACollidorComponent const& cpy)
		: Engine::AComponent(cpy)
	{

	}

	ACollidorComponent::~ACollidorComponent()
	{

	}

	std::string const	ACollidorComponent::getFamilyID() const
	{
		return (Engine::AComponent::COLLIDOR);
	}
}