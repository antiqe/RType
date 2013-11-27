#include "RenderImageComponent.hpp"
#include "Core.hpp"

RenderImageComponent::RenderImageComponent(std::string const& file)
	: Engine::ARenderComponent(),
	_dataModule(0),
	_positionComponent(0),
	_sizeComponent(0),
	_file(file),
	_img(0),
	_sourceModule(0)
{

}

RenderImageComponent::RenderImageComponent(RenderImageComponent const& cpy)
	: Engine::ARenderComponent(cpy),
	_dataModule(cpy._dataModule),
	_positionComponent(cpy._positionComponent),
	_sizeComponent(cpy._sizeComponent),
	_file(cpy._file),
	_img(cpy._img),
	_sourceModule(cpy._sourceModule)
{

}

RenderImageComponent::~RenderImageComponent()
{

}

void	RenderImageComponent::initialize()
{
	if (this->getOwner())
	{
		this->_positionComponent = dynamic_cast<Engine::APositionComponent<float, 2>*>(this->getOwner()->getComponent(Engine::AComponent::POSITION));
		this->_sizeComponent = dynamic_cast<Engine::ASizeComponent<2>*>(this->getOwner()->getComponent(Engine::AComponent::SIZE));
	}
	if ((this->_sourceModule = dynamic_cast<Engine::ASourceModule*>(Engine::Core::getInstance()->getInstance()->getModule(Engine::AModule::SOURCE))))
		this->_img = dynamic_cast<SFMLImage*>(this->_sourceModule->getImage(this->_file));
	this->_dataModule = dynamic_cast<Engine::ADataModule*>(Engine::Core::getInstance()->getInstance()->getModule(Engine::AModule::DATA));
}

void	RenderImageComponent::update()
{
	if (this->_img)
		this->_img->update();
}

void	RenderImageComponent::unload()
{

}

void	RenderImageComponent::draw(Engine::IRender* render)
{
	if (this->_img)
	{
		if (this->_sizeComponent)
		{
			Ultra::Vector<size_t, 2>	size = this->_sizeComponent->getSize();
			if (this->_dataModule)
			{
				size.setCoordinate(size.getCoordinate(Ultra::X) * this->_dataModule->getAttr<size_t>("winWidth") / this->_dataModule->getAttr<size_t>("mapWidth"), Ultra::X);
				size.setCoordinate(size.getCoordinate(Ultra::Y) * this->_dataModule->getAttr<size_t>("winHeight") / this->_dataModule->getAttr<size_t>("mapHeight"), Ultra::Y);
			}
			this->_img->setSize(Ultra::Vector2D<size_t>(size.getCoordinate(Ultra::X), size.getCoordinate(Ultra::Y)));
		}
		if (this->_positionComponent)
		{
			Ultra::Vector<float, 2>	position = this->_positionComponent->getPosition();
			if (this->_dataModule)
			{
				position.setCoordinate((float)(position.getCoordinate(Ultra::X) * this->_dataModule->getAttr<size_t>("winWidth") / this->_dataModule->getAttr<size_t>("mapWidth")), Ultra::X);
				position.setCoordinate((float)(position.getCoordinate(Ultra::Y) * this->_dataModule->getAttr<size_t>("winHeight") / this->_dataModule->getAttr<size_t>("mapHeight")), Ultra::Y);
			}
			this->_img->setPosition(Ultra::Vector2D<int>((int)position.getCoordinate(Ultra::X), (int)position.getCoordinate(Ultra::Y)));
		}
		this->_img->draw(render);
	}
}

Engine::IImage*	RenderImageComponent::getImage() const
{
	return (this->_img);
}

std::string const	RenderImageComponent::getID() const
{
	return ("renderImage");
}

RenderImageComponent*	RenderImageComponent::clone() const
{
	return (new RenderImageComponent(*this));
}