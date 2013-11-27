#include "HGauge.hpp"

namespace Engine
{
	HGauge::HGauge(std::string const &name, std::string const &backgroundFile, std::string const &filledFile, int percent)
		: AGauge(name, backgroundFile, filledFile, percent)
	{
	}

	HGauge::~HGauge()
	{
	}

	void	HGauge::draw(Engine::IRender* render)
	{
		this->_filledImg->setPosition(this->_globalPosition);
		this->_filledImg->setSize(Ultra::Vector2D<size_t>(this->getWidth() * this->_percent / 100, this->getHeight()));
		this->_filledImg->draw(render);
		this->_bgImg->setPosition(this->_globalPosition);
		this->_bgImg->setSize(this->_size);
		this->_bgImg->draw(render);
	}
}
