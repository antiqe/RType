#include "ASlider.hpp"
#include "Event.hpp"
#include "Core.hpp"
#include "ScopeLock.hpp"

//
// CTOR / DTOR
//

namespace Engine
{
	ASlider::ASlider(std::string const &name, std::string const &normalFile, std::string const &cursorNormalFile,
		std::string const &cursorClickedFile, std::string const &cursorHoverFile,
		Engine::Callback::EventFunction moveCursorCallback, int min, int max, int defaultValue)
		: Engine::Widget(name), _value(defaultValue), _max(max), _min(min)
	{
		this->_file = normalFile;
		this->_cursor = new SliderCursor(name, cursorNormalFile, cursorClickedFile, cursorHoverFile, moveCursorCallback);
		this->addChild(this->_cursor);
		this->setSize(0, 0);
		this->setPosition(0, 0);
	}

	ASlider::~ASlider()
	{
	}

	//
	// LIFE-CYCLE
	//

	void	ASlider::initialize()
	{
		if ((this->_sourceModule = dynamic_cast<ASourceModule*>(Engine::Core::getInstance()->getModule(Engine::AModule::SOURCE))))
		{
			Ultra::ScopeLock	lock(Engine::Core::getInstance()->access(Engine::AModule::SOURCE));
			this->_img = this->_sourceModule->getImage(this->_file);
		}
	}

	void	ASlider::update()
	{
		(this->_max - this->_min <= 0 ?	this->hide() : this->show()); // TODO: why the fuck are you blinking ?
		Widget::update();
	}

	void	ASlider::unload()
	{
		Widget::unload();
	}

	void	ASlider::draw(Engine::IRender* render)
	{
		this->_img->setPosition(this->_globalPosition);
		this->_img->setSize(this->_size);
		this->_img->draw(render);
	}

	//
	// PUBLIC FUNCTIONS
	//

	void	ASlider::scroll(int delta)
	{
		delta = -delta;
		if (delta < 0 && this->_value + delta <= this->_min)
			this->setValue(this->_min);
		else if (delta > 0 && this->_value + delta >= this->_max)
			this->setValue(this->_max);
		else
			this->setValue(this->_value + delta);
	}

	//
	// GETTER / SETTER
	//

	int				ASlider::getValue() const
	{
		return (this->_value);
	}

	int				ASlider::getMax() const
	{
		return (this->_max);
	}

	void			ASlider::setMax(int max)
	{
		this->_max = max;
		this->setValue(this->_value);
	}

	int				ASlider::getMin() const
	{
		return (this->_min);
	}

	void			ASlider::setMin(int min)
	{
		this->_min = min;
		this->setValue(this->_value);
	}

	unsigned int	ASlider::getCursorWidth() const
	{
		return (this->_cursor->getWidth());
	}

	unsigned int	ASlider::getCursorHeight() const
	{
		return (this->_cursor->getHeight());
	}

	void			ASlider::setCursorSize(unsigned int x, unsigned int y)
	{
		this->_cursor->setSize(x, y);
	}

	int				ASlider::getCursorX() const
	{
		return (this->_cursor->getX());
	}

	int				ASlider::getCursorY() const
	{
		return (this->_cursor->getY());
	}

	void			ASlider::setCursorPosition(int x, int y)
	{
		return (this->_cursor->setPosition(x, y));
	}

	void	ASlider::hide()
	{
		Widget::hide();
		this->_cursor->hide();
	}

	void ASlider::show()
	{
		Widget::show();
		this->_cursor->show();
	}
}