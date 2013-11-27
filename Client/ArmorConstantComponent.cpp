#include "Core.hpp"
#include "ADataModule.hpp"
#include "AModule.hpp"
#include "ArmorConstantComponent.hpp"
#include "GameObject.hpp"

ArmorConstantComponent::ArmorConstantComponent(short armor, short min, short max)
	: Engine::AArmorComponent(armor, min, max)
{

}

ArmorConstantComponent::ArmorConstantComponent(ArmorConstantComponent const& cpy)
	: Engine::AArmorComponent(cpy)
{
}

ArmorConstantComponent::~ArmorConstantComponent()
{

}

void	ArmorConstantComponent::initialize()
{

}

void	ArmorConstantComponent::update()
{

}

void	ArmorConstantComponent::unload()
{

}

Engine::AComponent* ArmorConstantComponent::clone() const
{
	return (new ArmorConstantComponent(*this));
}

std::string const	ArmorConstantComponent::getID() const
{
	return ("armorConstant");
}
