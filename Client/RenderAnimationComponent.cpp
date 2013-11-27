#include "RenderAnimationComponent.hpp"
#include "Core.hpp"

RenderAnimationComponent::RenderAnimationComponent(std::string const& file)
	: Engine::ARenderComponent(),
	_dataModule(0),
	_positionComponent(0),
	_sizeComponent(0),
	_file(file),
	_animation(0),
	_sourceModule(0)
{

}

RenderAnimationComponent::RenderAnimationComponent(RenderAnimationComponent const& cpy)
	: Engine::ARenderComponent(cpy),
	_dataModule(cpy._dataModule),
	_positionComponent(cpy._positionComponent),
	_sizeComponent(cpy._sizeComponent),
	_file(cpy._file),
	_animation(cpy._animation),
	_sourceModule(cpy._sourceModule)
{

}

RenderAnimationComponent::~RenderAnimationComponent()
{

}

void	RenderAnimationComponent::initialize()
{
	if (this->getOwner())
	{
		this->_positionComponent = dynamic_cast<Engine::APositionComponent<float, 2>*>(this->getOwner()->getComponent(Engine::AComponent::POSITION));
		this->_sizeComponent = dynamic_cast<Engine::ASizeComponent<2>*>(this->getOwner()->getComponent(Engine::AComponent::SIZE));
	}
	if ((this->_sourceModule = dynamic_cast<Engine::ASourceModule*>(Engine::Core::getInstance()->getInstance()->getModule(Engine::AModule::SOURCE))))
	{
		if ((this->_animation = dynamic_cast<SFMLAnimation*>(this->_sourceModule->getImage(this->_file))))
			this->_context = this->_animation->addContext();
	}
	this->_dataModule = dynamic_cast<Engine::ADataModule*>(Engine::Core::getInstance()->getInstance()->getModule(Engine::AModule::DATA));
}

void	RenderAnimationComponent::update()
{
	if (this->_animation)
		this->_animation->update();
}

void	RenderAnimationComponent::unload()
{
	if (this->_animation)
		this->_animation->delContext(this->_context);
}

void	RenderAnimationComponent::draw(Engine::IRender* render)
{
	if (this->_animation)
	{
		if (this->_sizeComponent)
		{
			Ultra::Vector<size_t, 2>	size = this->_sizeComponent->getSize();
			if (this->_dataModule)
			{
				size.setCoordinate(size.getCoordinate(Ultra::X) * this->_dataModule->getAttr<size_t>("winWidth") / this->_dataModule->getAttr<size_t>("mapWidth"), Ultra::X);
				size.setCoordinate(size.getCoordinate(Ultra::Y) * this->_dataModule->getAttr<size_t>("winHeight") / this->_dataModule->getAttr<size_t>("mapHeight"), Ultra::Y);
			}
			this->_animation->setSize(Ultra::Vector2D<size_t>(size.getCoordinate(Ultra::X), size.getCoordinate(Ultra::Y)));
		}
		if (this->_positionComponent)
		{
			Ultra::Vector<float, 2>	position = this->_positionComponent->getPosition();
			if (this->_dataModule)
			{
				position.setCoordinate((float)(position.getCoordinate(Ultra::X) * this->_dataModule->getAttr<size_t>("winWidth") / this->_dataModule->getAttr<size_t>("mapWidth")), Ultra::X);
				position.setCoordinate((float)(position.getCoordinate(Ultra::Y) * this->_dataModule->getAttr<size_t>("winHeight") / this->_dataModule->getAttr<size_t>("mapHeight")), Ultra::Y);
			}
			this->_animation->setPosition(Ultra::Vector2D<int>((int)position.getCoordinate(Ultra::X), (int)position.getCoordinate(Ultra::Y)));
		}
		this->_animation->draw(render);
	}
}

Engine::IImage*	RenderAnimationComponent::getImage() const
{
	return (this->_animation);
}

std::string const	RenderAnimationComponent::getID() const
{
	return ("renderAnimation");
}

RenderAnimationComponent*	RenderAnimationComponent::clone() const
{
	return (new RenderAnimationComponent(*this));
}