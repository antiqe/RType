#include "AArmorComponent.hpp"

namespace Engine
{
	AArmorComponent::AArmorComponent(short armor, short min, short max)
		: Engine::AComponent(), _armor(armor), _min(min), _max(max)
	{
		this->setArmor(armor);
	}

	AArmorComponent::AArmorComponent(AArmorComponent const& cpy)
		: Engine::AComponent(cpy), _armor(cpy._armor), _min(cpy._min), _max(cpy._max)
	{

	}

	AArmorComponent::~AArmorComponent()
	{

	}

	std::string const	AArmorComponent::getFamilyID() const
	{
		return (Engine::AComponent::ARMOR);
	}

	short	AArmorComponent::getArmor() const
	{
		return (this->_armor);
	}

	void	AArmorComponent::setArmor(short armor)
	{
		this->_armor = armor < this->_min ? this->_min : (armor > this->_max ? this->_max : armor);
	}
}