#include "Core.hpp"
#include "ADataModule.hpp"
#include "AModule.hpp"
#include "LifeConstantComponent.hpp"
#include "GameObject.hpp"

LifeConstantComponent::LifeConstantComponent(unsigned int max)
	: Engine::ALifeComponent(max)
{

}

LifeConstantComponent::LifeConstantComponent(unsigned int current, unsigned int max)
	: Engine::ALifeComponent(current, max)
{

}


LifeConstantComponent::LifeConstantComponent(LifeConstantComponent const& cpy)
	: Engine::ALifeComponent(cpy)
{

}

LifeConstantComponent::~LifeConstantComponent()
{

}

void	LifeConstantComponent::initialize()
{
	if (this->getOwner())
		this->_armorComponent = dynamic_cast<Engine::AArmorComponent*>(this->getOwner()->getComponent(AComponent::ARMOR));
}

void	LifeConstantComponent::update()
{

}

void	LifeConstantComponent::unload()
{

}

Engine::AComponent* LifeConstantComponent::clone() const
{
	return (new LifeConstantComponent(*this));
}

std::string const	LifeConstantComponent::getID() const
{
	return ("lifeConstant");
}

void	LifeConstantComponent::takeDamage(unsigned int damage)
{

	this->setCurrentLife(this->_current - (damage - (damage * (this->_armorComponent ? this->_armorComponent->getArmor() : 0) / 100)));
}

void	LifeConstantComponent::heal(unsigned int heal)
{
	this->setCurrentLife(this->_current + heal);
}
