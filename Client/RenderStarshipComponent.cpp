#include "RenderStarshipComponent.hpp"
#include "Core.hpp"

RenderStarshipComponent::RenderStarshipComponent(std::string const& normal, std::string const& up, std::string const& down)
	: Engine::ARenderComponent(),
	_current(RenderStarshipComponent::NORMAL),
	_dataModule(0),
	_vectorComponent(0),
	_positionComponent(0),
	_sizeComponent(0),
	_sourceModule(0)
{
	this->_file[RenderStarshipComponent::NORMAL] = normal;
	this->_file[RenderStarshipComponent::UP] = up;
	this->_file[RenderStarshipComponent::DOWN] = down;
	this->_img[RenderStarshipComponent::NORMAL] = 0;
	this->_img[RenderStarshipComponent::UP] = 0;
	this->_img[RenderStarshipComponent::DOWN] = 0;
}

RenderStarshipComponent::RenderStarshipComponent(RenderStarshipComponent const& cpy)
	: Engine::ARenderComponent(cpy),
	_current(cpy._current),
	_dataModule(cpy._dataModule),
	_vectorComponent(cpy._vectorComponent),
	_positionComponent(cpy._positionComponent),
	_sizeComponent(cpy._sizeComponent),
	_sourceModule(cpy._sourceModule)
{
	for (int i = 0; i < (int)RenderStarshipComponent::STATUSSIZE; ++i)
	{
		this->_file[i] = cpy._file[i];
		this->_img[i] = cpy._img[i];
	}
}

RenderStarshipComponent::~RenderStarshipComponent()
{

}

void	RenderStarshipComponent::initialize()
{
	if (this->getOwner())
	{
		this->_positionComponent = dynamic_cast<Engine::APositionComponent<float, 2>*>(this->getOwner()->getComponent(Engine::AComponent::POSITION));
		this->_sizeComponent = dynamic_cast<Engine::ASizeComponent<2>*>(this->getOwner()->getComponent(Engine::AComponent::SIZE));
		this->_vectorComponent = dynamic_cast<Engine::AVectorComponent<float, 2>*>(this->getOwner()->getComponent(Engine::AComponent::VECTOR));
	}
	if ((this->_sourceModule = dynamic_cast<Engine::ASourceModule*>(Engine::Core::getInstance()->getInstance()->getModule(Engine::AModule::SOURCE))))
		for (int i = 0; i < (int)RenderStarshipComponent::STATUSSIZE; ++i)
			this->_img[i] = dynamic_cast<SFMLImage*>(this->_sourceModule->getImage(this->_file[i]));
	this->_dataModule = dynamic_cast<Engine::ADataModule*>(Engine::Core::getInstance()->getInstance()->getModule(Engine::AModule::DATA));
}

void	RenderStarshipComponent::update()
{
	if (this->_vectorComponent)
	{
		Ultra::Vector<float, 2>	vector = this->_vectorComponent->getVector();
		if (vector.getCoordinate(Ultra::Y) > 0.0f)
			this->_current = RenderStarshipComponent::DOWN;
		else if (vector.getCoordinate(Ultra::Y) < 0.0f)
			this->_current = RenderStarshipComponent::UP;
		else
			this->_current = RenderStarshipComponent::NORMAL;
	}
	if (this->_img[this->_current])
		this->_img[this->_current]->update();
}

void	RenderStarshipComponent::unload()
{

}

void	RenderStarshipComponent::draw(Engine::IRender* render)
{
	if (this->_img[this->_current])
	{
		if (this->_sizeComponent)
		{
			Ultra::Vector<size_t, 2>	size = this->_sizeComponent->getSize();
			if (this->_dataModule)
			{
				size.setCoordinate(size.getCoordinate(Ultra::X) * this->_dataModule->getAttr<size_t>("winWidth") / this->_dataModule->getAttr<size_t>("mapWidth"), Ultra::X);
				size.setCoordinate(size.getCoordinate(Ultra::Y) * this->_dataModule->getAttr<size_t>("winHeight") / this->_dataModule->getAttr<size_t>("mapHeight"), Ultra::Y);
			}
			this->_img[this->_current]->setSize(Ultra::Vector2D<size_t>(size.getCoordinate(Ultra::X), size.getCoordinate(Ultra::Y)));
		}
		if (this->_positionComponent)
		{
			Ultra::Vector<float, 2>	position = this->_positionComponent->getPosition();
			if (this->_dataModule)
			{
				position.setCoordinate((float)(position.getCoordinate(Ultra::X) * this->_dataModule->getAttr<size_t>("winWidth") / this->_dataModule->getAttr<size_t>("mapWidth")), Ultra::X);
				position.setCoordinate((float)(position.getCoordinate(Ultra::Y) * this->_dataModule->getAttr<size_t>("winHeight") / this->_dataModule->getAttr<size_t>("mapHeight")), Ultra::Y);
			}
			this->_img[this->_current]->setPosition(Ultra::Vector2D<int>((int)position.getCoordinate(Ultra::X), (int)position.getCoordinate(Ultra::Y)));
		}
		this->_img[this->_current]->draw(render);
	}
}

Engine::IImage*	RenderStarshipComponent::getImage() const
{
	return (this->_img[this->_current]);
}

std::string const	RenderStarshipComponent::getID() const
{
	return ("renderStarship");
}

RenderStarshipComponent*	RenderStarshipComponent::clone() const
{
	return (new RenderStarshipComponent(*this));
}