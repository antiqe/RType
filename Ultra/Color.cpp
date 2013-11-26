#include "Color.hpp"

namespace Ultra
{
	Color::Color(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha)
	{
		this->_rgba[Color::RED] = red;
		this->_rgba[Color::BLUE] = blue;
		this->_rgba[Color::GREEN] = green;
		this->_rgba[Color::ALPHA] = alpha;
	}

	Color::Color(unsigned char rgb, unsigned char alpha)
	{
		this->_rgba[Color::RED] = rgb;
		this->_rgba[Color::BLUE] = rgb;
		this->_rgba[Color::GREEN] = rgb;
		this->_rgba[Color::ALPHA] = alpha;
	}

	Color::Color(unsigned char rgba)
	{
		this->_rgba[Color::RED] = rgba;
		this->_rgba[Color::BLUE] = rgba;
		this->_rgba[Color::GREEN] = rgba;
		this->_rgba[Color::ALPHA] = rgba;
	}

	Color::Color(Color const& cpy)
	{
		this->_rgba[Color::RED] = cpy._rgba[Color::RED];
		this->_rgba[Color::BLUE] = cpy._rgba[Color::BLUE];
		this->_rgba[Color::GREEN] = cpy._rgba[Color::GREEN];
		this->_rgba[Color::ALPHA] = cpy._rgba[Color::ALPHA];
	}

	Color::Color()
	{
		this->_rgba[Color::RED] = 255;
		this->_rgba[Color::BLUE] = 255;
		this->_rgba[Color::GREEN] = 255;
		this->_rgba[Color::ALPHA] = 255;
	}

	Color::~Color()
	{

	}

	Color&	Color::operator=(Color const& cpy)
	{
		if (this != &cpy)
		{
			this->_rgba[Color::RED] = cpy._rgba[Color::RED];
			this->_rgba[Color::BLUE] = cpy._rgba[Color::BLUE];
			this->_rgba[Color::GREEN] = cpy._rgba[Color::GREEN];
			this->_rgba[Color::ALPHA] = cpy._rgba[Color::ALPHA];
		}
		return (*this);
	}

	void	Color::setComposante(Color::Composante composante, unsigned char value)
	{
		this->_rgba[composante] = value;
	}

	unsigned char	Color::getComposante(Color::Composante composante) const
	{
		return (this->_rgba[composante]);
	}
}