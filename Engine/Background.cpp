#include "Background.hpp"
#include "Core.hpp"
#include "ScopeLock.hpp"

namespace Engine
{
	Background::Background(std::string const& name, std::string const& file, Ultra::Color const& color)
		: Engine::Widget(name), _sourceModule(0), _color(color), _file(file), _img(0)
	{

	}

	Background::~Background()
	{

	}

	void	Background::initialize()
	{
		if ((this->_sourceModule = dynamic_cast<ASourceModule*>(Engine::Core::getInstance()->getModule(Engine::AModule::SOURCE))))
		{
			Ultra::ScopeLock	lock(Engine::Core::getInstance()->access(Engine::AModule::SOURCE));
			this->_img = this->_sourceModule->getImage(this->_file);
		}
	}

	void	Background::update()
	{
		if (this->_img)
			this->_img->update();
	}

	void	Background::unload()
	{
		if (this->_img)
			this->_img->unload();
	}

	void	Background::draw(Engine::IRender* render)
	{
		if (this->_img)
		{
			this->_img->setSize(this->_size);
			this->_img->setPosition(this->_globalPosition);
			this->_img->draw(render);
		}
	}
}