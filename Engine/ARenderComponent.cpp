#include "ARenderComponent.hpp"

namespace Engine
{
	ARenderComponent::ARenderComponent()
		: Engine::AComponent()
	{

	}

	ARenderComponent::ARenderComponent(ARenderComponent const& cpy)
		: Engine::AComponent(cpy)
	{

	}

	ARenderComponent::~ARenderComponent()
	{

	}

	std::string const	ARenderComponent::getFamilyID() const
	{
		return (Engine::AComponent::RENDER);
	}
}