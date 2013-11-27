#include "Core.hpp"
#include "ADataModule.hpp"
#include "AModule.hpp"
#include "Size2DComponent.hpp"
#include "GameObject.hpp"

Size2DComponent::Size2DComponent(size_t width, size_t height)
	: Engine::ASizeComponent<2>()
{
	this->_size.setCoordinate(width, Ultra::X);
	this->_size.setCoordinate(height, Ultra::Y);
}

Size2DComponent::Size2DComponent(Size2DComponent const& cpy)
	: ASizeComponent(cpy)
{

}

Size2DComponent::~Size2DComponent()
{

}

void	Size2DComponent::initialize()
{

}

void	Size2DComponent::update()
{

}

void	Size2DComponent::unload()
{
}

Engine::AComponent* Size2DComponent::clone() const
{
	return (new Size2DComponent(*this));
}

std::string const	Size2DComponent::getID() const
{
	return ("size2D");
}
