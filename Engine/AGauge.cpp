#include "AGauge.hpp"
#include "VSlider.hpp"
#include "MouseEvent.hpp"
#include "Core.hpp"
#include "ScopeLock.hpp"

//
// CTOR / DTOR
//

namespace Engine
{
	AGauge::AGauge(std::string const &name, std::string const &backgroundFile, std::string const &filledFile, int percent)
		: Engine::Widget(name), _percent(percent), _bgFile(backgroundFile), _filledFile(filledFile)
	{
	}

	AGauge::~AGauge()
	{
	}

	//
	// LIFE-CYCLE
	//

	void	AGauge::initialize()
	{
		if ((this->_sourceModule = dynamic_cast<Engine::ASourceModule*>(Engine::Core::getInstance()->getModule(Engine::AModule::SOURCE))))
		{
			Ultra::ScopeLock	lock(Engine::Core::getInstance()->access(Engine::AModule::SOURCE));
			this->_bgImg = this->_sourceModule->getImage(this->_bgFile);
			this->_filledImg = this->_sourceModule->getImage(this->_filledFile);
		}
	}

	void	AGauge::update()
	{
	}

	void	AGauge::unload()
	{
	}

	//
	// GETTER / SETTER
	//

	int		AGauge::getPercent() const
	{
		return (this->_percent);
	}

	void	AGauge::setPercent(int percent)
	{
		this->_percent = percent;
	}

	void	AGauge::setFilledImg(std::string const &filledFile)
	{
		Ultra::ScopeLock	lock(Engine::Core::getInstance()->access(Engine::AModule::SOURCE));
		this->_filledFile = filledFile;
		this->_filledImg = this->_sourceModule->getImage(this->_filledFile);
	}
}