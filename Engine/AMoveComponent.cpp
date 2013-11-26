#include "AMoveComponent.hpp"

namespace Engine
{
	AMoveComponent::AMoveComponent()
		: Engine::AComponent()
	{

	}

	AMoveComponent::AMoveComponent(AMoveComponent const& cpy)
		: Engine::AComponent(cpy)
	{

	}

	AMoveComponent::~AMoveComponent()
	{

	}

	std::string const	AMoveComponent::getFamilyID() const
	{
		return (Engine::AComponent::MOVE);
	}
}
