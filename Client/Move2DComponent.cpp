#include "Core.hpp"
#include "ADataModule.hpp"
#include "AModule.hpp"
#include "Move2DComponent.hpp"
#include "GameObject.hpp"

Move2DComponent::Move2DComponent()
	: Engine::AMoveComponent(), _vectorComponent(0), _speedComponent(0)
{

}

Move2DComponent::Move2DComponent(Move2DComponent const& cpy)
	: AMoveComponent(cpy), _vectorComponent(0), _speedComponent(0)
{

}

Move2DComponent::~Move2DComponent()
{

}

void	Move2DComponent::initialize()
{
	if (this->getOwner())
	{
		this->_positionComponent = dynamic_cast<Engine::APositionComponent<float, 2>*>(this->getOwner()->getComponent(AComponent::POSITION));
		this->_vectorComponent = dynamic_cast<Engine::AVectorComponent<float, 2>*>(this->getOwner()->getComponent(AComponent::VECTOR));
		this->_speedComponent = dynamic_cast<Engine::ASpeedComponent*>(this->getOwner()->getComponent(AComponent::SPEED));
	}
}

void	Move2DComponent::update()
{
	if (this->_positionComponent && this->_vectorComponent)
	{
		Ultra::Vector<float, 2>	position = this->_positionComponent->getPosition();
		Ultra::Vector<float, 2>	vector = this->_vectorComponent->getVector();
		float					speed = this->_speedComponent ? this->_speedComponent->getSpeed() : 1.0f;
		position.setCoordinate(position.getCoordinate(Ultra::X) + (vector.getCoordinate(Ultra::X) * speed), Ultra::X);
		position.setCoordinate(position.getCoordinate(Ultra::Y) + (vector.getCoordinate(Ultra::Y) * speed), Ultra::Y);
		this->_positionComponent->setPosition(position);
	}
}

void	Move2DComponent::unload()
{
}

Engine::AComponent* Move2DComponent::clone() const
{
	return (new Move2DComponent(*this));
}

std::string const	Move2DComponent::getID() const
{
	return ("move2D");
}
