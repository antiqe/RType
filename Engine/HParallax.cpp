#include "HParallax.hpp"
#include "Core.hpp"

namespace Engine
{
	HParallax::HParallax(std::string const& name, std::string const& file, float z, Ultra::Color const& color)
		: AParallax(name, file, z, color)
	{

	}

	HParallax::~HParallax()
	{

	}

	void	HParallax::initialize()
	{
		this->_img.initialize();
	}

	void	HParallax::update()
	{
		this->_img.update();
		if (this->_x[BEGIN] != this->_x[END])
			this->scroll();
	}

	void	HParallax::unload()
	{
		this->_img.unload();
	}

	void	HParallax::draw(Engine::IRender* render)
	{
		this->_img.setSize(this->_size.getX(), this->_size.getY());
		this->_img.setPosition((int)this->_x[BEGIN], this->_globalPosition.getY());
		this->_img.draw(render);
		this->_img.setPosition((int)this->_x[END], this->_globalPosition.getY());
		this->_img.draw(render);
	}

	void	HParallax::scroll()
	{
		for (int i = 0; i < AParallax::TYPESIZE; ++i)
			this->_x[i] = this->_x[i] - (1.0f * this->_z);
		if (this->_x[END] < (float)this->_globalPosition.getX())
		{
			this->_x[AParallax::BEGIN] = (float)this->_globalPosition.getX();
			this->_x[AParallax::END] = (float)(this->_x[AParallax::BEGIN] + this->_size.getX());
		}
	}
}