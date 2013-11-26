#include "AParallax.hpp"

namespace Engine
{
	AParallax::AParallax(std::string const& name, std::string const& file, float z, Ultra::Color const& color)
		: Engine::Widget(name), _z(z), _img(Background("", file, color))
	{
		for (int i = 0; i < AParallax::TYPESIZE; ++i)
		{
			this->_x[i] = 0.0f;
			this->_y[i] = 0.0f;
		}
	}

	AParallax::~AParallax()
	{

	}

	void	AParallax::setWidth(size_t w)
	{
		Widget::setWidth(w);
		this->_x[AParallax::END] = (float)(this->_x[AParallax::BEGIN] + this->_size.getX());
	}

	void	AParallax::setHeight(size_t h)
	{
		Widget::setHeight(h);
		this->_y[AParallax::END] = (float)(this->_y[AParallax::BEGIN] + this->_size.getY());
	}

	void	AParallax::setX(int x)
	{
		Widget::setX(x);
		this->_x[AParallax::BEGIN] = (float)this->_globalPosition.getX();
		this->_x[AParallax::END] = (float)(this->_x[AParallax::BEGIN] + this->_size.getX());
	}

	void	AParallax::setY(int y)
	{
		Widget::setY(y);
		this->_y[AParallax::BEGIN] = (float)this->_globalPosition.getY();
		this->_y[AParallax::END] = (float)(this->_y[AParallax::BEGIN] + this->_size.getY());
	}

	void	AParallax::setLocalX(int x)
	{
		Widget::setLocalX(x);
		this->_x[AParallax::BEGIN] = (float)this->_globalPosition.getX();
		this->_x[AParallax::END] = (float)(this->_x[AParallax::BEGIN] + this->_size.getX());
	}

	void	AParallax::setLocalY(int y)
	{
		Widget::setLocalY(y);
		this->_y[AParallax::BEGIN] = (float)this->_globalPosition.getY();
		this->_y[AParallax::END] = (float)(this->_y[AParallax::BEGIN] + this->_size.getY());
	}
}