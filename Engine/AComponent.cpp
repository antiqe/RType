#include "AComponent.hpp"

namespace Engine
{
	std::string const	AComponent::RENDER = "render";
	std::string const	AComponent::POSITION = "position";
	std::string const	AComponent::ROTATION = "rotation";
	std::string const	AComponent::MOVE = "move";
	std::string const	AComponent::VECTOR = "vector";
	std::string const	AComponent::SPEED = "speed";
	std::string const	AComponent::LIFE = "life";
	std::string const	AComponent::COLLIDOR = "collidor";
	std::string const	AComponent::SIZE = "size";
	std::string const	AComponent::SHOOT = "shoot";
	std::string const	AComponent::ARMOR = "armor";
	std::string const	AComponent::EXPLODE = "explode";
	std::string const	AComponent::SHIELD = "shield";
	std::string const	AComponent::INVINCIBILITY = "invincibility";
	std::string const	AComponent::NETWORK = "network";
	std::string const	AComponent::SCORE = "score";
	std::string const	AComponent::LEVEL = "level";
	std::string const	AComponent::SOUND = "sound";

	AComponent::Compare::Compare(std::string const& id)
		: _id(id)
	{}

	AComponent::Compare::~Compare()
	{

	};

	bool	AComponent::Compare::operator()(AComponent* const& component) const
	{
		return (this->_id == component->getFamilyID());
	}

	AComponent::AComponent()
		: _owner(0)
	{

	}

	AComponent::AComponent(AComponent const& /*cpy */)
		: _owner(0)
	{

	}

	AComponent::~AComponent()
	{

	}

	GameObject*	AComponent::getOwner() const
	{
		return (this->_owner);
	}
}
