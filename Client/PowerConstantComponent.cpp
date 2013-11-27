#include "Core.hpp"
#include "ADataModule.hpp"
#include "AModule.hpp"
#include "PowerConstantComponent.hpp"
#include "GameObject.hpp"

PowerConstantComponent::PowerConstantComponent(unsigned short power)
	: Engine::APowerComponent(power)
{

}

PowerConstantComponent::PowerConstantComponent(PowerConstantComponent const& cpy)
	: Engine::APowerComponent(cpy)
{
}

PowerConstantComponent::~PowerConstantComponent()
{

}

void	PowerConstantComponent::initialize()
{

}

void	PowerConstantComponent::update()
{

}

void	PowerConstantComponent::unload()
{

}

Engine::AComponent* PowerConstantComponent::clone() const
{
	return (new PowerConstantComponent(*this));
}

std::string const	PowerConstantComponent::getID() const
{
	return ("powerConstant");
}
