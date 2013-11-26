#include  <iostream>

#include "Position2DComponent.hpp"

Position2DComponent::Position2DComponent()
	: Engine::APositionComponent<float, 2>()
{

}

Position2DComponent::Position2DComponent(Position2DComponent const& cpy)
	: Engine::APositionComponent<float, 2>(cpy)
{

}

Position2DComponent::~Position2DComponent()
{
}

void			Position2DComponent::initialize()
{

}

void			Position2DComponent::update()
{

}

void			Position2DComponent::unload()
{
		
}

float			Position2DComponent::getX() const
{
	return (this->_position.getCoordinate(Ultra::X));
}

float			Position2DComponent::getY() const
{
	return (this->_position.getCoordinate(Ultra::Y));
}

void			Position2DComponent::setX(float x)
{
	this->_position.setCoordinate(x, Ultra::X);
}

void			Position2DComponent::setY(float y)
{
	this->_position.setCoordinate(y, Ultra::Y);
}

Engine::AComponent*  Position2DComponent::clone() const
{
	return (new Position2DComponent(*this));
}

std::string const	Position2DComponent::getID() const
{
	return ("position2D");
}
