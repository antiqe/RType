#include <SFML/Graphics.hpp>

#include "RenderModule.hpp"
#include "Core.hpp"
#include "Singleton.hpp"
#include "ScopeLock.hpp"
#include "SFMLRender.hpp"

#include "SFMLText.hpp"

RenderModule::RenderModule()
	: ARenderModule(new SFMLRender()), _stateModule(0), _dataModule(0)
{

}

RenderModule::~RenderModule()
{

}

void	RenderModule::initialize()
{
	if (!this->_render)
		Engine::Core::getInstance()->stop();
	if (this->_owner)
	{
		this->_stateModule = dynamic_cast<StateModule*>(this->_owner->getModule(AModule::STATE));
		if ((this->_dataModule = dynamic_cast<DataModule*>(this->_owner->getModule(AModule::DATA))))
		{
			this->_render->open(this->_dataModule->getAttr<size_t>("winWidth"),
				this->_dataModule->getAttr<size_t>("winHeight"),
				this->_dataModule->getAttr<std::string>("winTitle"),
				this->_dataModule->getAttr<unsigned long>("winMode"));
			this->_render->setPosition(this->_dataModule->getAttr<int>("winX"), this->_dataModule->getAttr<int>("winY"));
		}
		else
			this->_render->open(800, 600, "R-TYPE", sf::Style::Close | sf::Style::Titlebar);
	}
}

void	RenderModule::update()
{
	if (this->_dataModule)
	{ 
		size_t			width;
		size_t			height;
		std::string		title;
		unsigned long	mode;
		{
			Ultra::ScopeLock	lock(Engine::Core::getInstance()->access(AModule::DATA));
			width = this->_dataModule->getAttr<size_t>("winWidth");
			height = this->_dataModule->getAttr<size_t>("winHeight");
			title = this->_dataModule->getAttr<std::string>("winTitle");
			mode = this->_dataModule->getAttr<unsigned long>("winMode");
		}
		if (width != this->_render->getWidth())
			this->_render->setWidth(width);
		if (height != this->_render->getHeight())
			this->_render->setHeight(height);
		if (title != this->_render->getTitle())
			this->_render->setTitle(title);
		if (mode != this->_render->getMode())
			this->_render->setMode(mode);
	}
}

void	RenderModule::draw()
{
	this->_render->clear();
	if (this->_stateModule)
	{
		Ultra::ScopeLock		lock(Engine::Core::getInstance()->access(AModule::STATE));
		if (this->_stateModule->top())
		{
			std::list<Engine::Widget*>	list = this->_stateModule->top()->getAllChild();
			std::list<Engine::Widget*>	tmp;
			while (!list.empty())
			{
				if (!list.front()->isHidden())
				{
					list.front()->draw(this->_render);
					tmp = list.front()->getAllChild();
					list.splice(list.end(), tmp);
				}
				list.pop_front();
			}
		}
	}
	this->_render->display();
}

void	RenderModule::unload()
{
	if (this->_render)
	{
		this->_render->close();
		delete this->_render;
		this->_render = 0;
		this->_dataModule = 0;
	}
}