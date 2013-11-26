#include <math.h>

#include "Core.hpp"
#include "ADataModule.hpp"
#include "AModule.hpp"
#include "Vector2DComponent.hpp"
#include "GameObject.hpp"

Vector2DComponent::Vector2DComponent()
	: Engine::AVectorComponent<float, 2>()
{

}

Vector2DComponent::Vector2DComponent(Vector2DComponent const& cpy)
	: AVectorComponent(cpy)
{

}

Vector2DComponent::~Vector2DComponent()
{

}

void	Vector2DComponent::initialize()
{

}

void	Vector2DComponent::update()
{

}

void	Vector2DComponent::unload()
{

}

Engine::AComponent* Vector2DComponent::clone() const
{
	return (new Vector2DComponent(*this));
}

std::string const	Vector2DComponent::getID() const
{
	return ("vector2D");
}
