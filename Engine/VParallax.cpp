#include "VParallax.hpp"

namespace Engine
{
	VParallax::VParallax(std::string const& name, std::string const& file, float z, Ultra::Color const& color)
		: AParallax(name, file, z, color)
	{

	}

	VParallax::~VParallax()
	{

	}

	void	VParallax::initialize()
	{
		this->_img.initialize();
	}

	void	VParallax::update()
	{
		this->_img.update();
		if (this->_y[BEGIN] != this->_y[END])
			this->scroll();
	}

	void	VParallax::unload()
	{
		this->_img.unload();
	}

	void	VParallax::draw(Engine::IRender* render)
	{
		this->_img.setSize(this->_size.getX(), this->_size.getY());
		this->_img.setPosition(this->_globalPosition.getX(), (int)this->_y[BEGIN]);
		this->_img.draw(render);
		this->_img.setPosition(this->_globalPosition.getX(), (int)this->_y[END]);
		this->_img.draw(render);
	}

	void	VParallax::scroll()
	{
		for (int i = 0; i < AParallax::TYPESIZE; ++i)
			this->_y[i] = this->_y[i] - (1.0f * this->_z);
		if (this->_y[END] < this->_globalPosition.getY())
		{
			this->_y[AParallax::BEGIN] = (float)this->_globalPosition.getY();
			this->_y[AParallax::END] = (float)(this->_x[AParallax::BEGIN] + this->_size.getY());
		}
	}
}