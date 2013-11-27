#include "VGauge.hpp"

namespace Engine
{
	VGauge::VGauge(std::string const &name, std::string const &backgroundFile, std::string const &filledFile, int percent)
		: AGauge(name, backgroundFile, filledFile, percent)
	{

	}

	VGauge::~VGauge()
	{

	}

	void	VGauge::draw(Engine::IRender* render)
	{
		this->_filledImg->setPosition(this->_globalPosition);
		this->_filledImg->setSize(Ultra::Vector2D<long unsigned int>(this->getWidth(), this->getHeight() * this->_percent / 100));
		this->_filledImg->draw(render);
		this->_bgImg->setPosition(this->_globalPosition);
		this->_bgImg->setSize(this->_size);
		this->_bgImg->draw(render);
	}
}
