#include "VSlider.hpp"
#include "VSliderCallback.hpp"
#include "SliderCursorCallback.hpp"
#include "MouseEvent.hpp"

//
// CTOR / DTOR
//

namespace Engine
{
	VSlider::VSlider(std::string const &name, std::string const &normalFile, 
		std::string const &cursorNormalFile, std::string const &cursorClickedFile,
		std::string const &cursorHoverFile, int min, int max, int defaultValue)
		: ASlider(name, normalFile, cursorNormalFile, cursorClickedFile, cursorHoverFile, 
		Callback::SliderCursor::mouseMoveY, min, max, defaultValue)
	{
	}

	VSlider::~VSlider()
	{
	}

	//
	// LIFE-CYCLE
	//

	void	VSlider::initialize()
	{
		ASlider::initialize();
		this->addEventListener(Engine::Event::MOUSE, Engine::MouseEvent::LEFT_CLICK, &Callback::VSlider::mouseClick);
		this->addEventListener(Engine::Event::MOUSE, Engine::MouseEvent::MOUSE_WHEEL, &Callback::VSlider::mouseWheel);
		Widget::initialize();
	}

	void	VSlider::unload()
	{
		this->removeEventListener(Engine::Event::MOUSE, Engine::MouseEvent::MOUSE_MOVE);
		this->removeEventListener(Engine::Event::MOUSE, Engine::MouseEvent::MOUSE_WHEEL);
		Widget::unload();
	}

	//
	// PUBLIC FUNCTIONS
	//

	void	VSlider::moveCursor(int y)
	{
		int v = (this->_max - this->_min);
		int d = this->getHeight();
		int hit = y - this->getY();
		int offset = this->getY() - (this->_cursor->getHeight() / 2);
		if (!hit)
			this->_cursor->setPosition(this->_cursor->getX(), offset);
		else
		{
			int nextSlice = 1;
			int interval = (d / v);
			while (hit > nextSlice * interval)
				nextSlice++;
			int slice = nextSlice - 1;
			if (hit - slice * (d / v) > nextSlice * (d / v) - hit)
			{
				this->_cursor->setPosition(this->_cursor->getX(), nextSlice * (d / v) + offset);
				this->_value = nextSlice;
			}
			else
			{
				this->_cursor->setPosition(this->_cursor->getX(), slice * (d / v) + offset);
				this->_value = slice;
			}
		}
	}

	//
	// SETTER
	//

	void	VSlider::setValue(int value)
	{
		this->_value = value;
		if (value == 0)
			this->moveCursor(this->getY());
		else
		{
			int sliceSize = this->getHeight() / (this->_max - this->_min);
			int target = this->_value - Ultra::Converter::abs<int>(this->_min);
			this->moveCursor(this->getY() + (target * sliceSize));
		}
	}

	void	VSlider::setWidth(size_t w)
	{
		this->_size.setX(w);
		this->_cursor->setSize(this->_size.getX(), this->_size.getY() / 10);
		this->setValue(this->_value);
	}

	void	VSlider::setHeight(size_t h)
	{
		this->_size.setY(h);
		this->_cursor->setSize(this->_size.getX(), this->_size.getY() / 10);
		this->setValue(this->_value);
	}

	void	VSlider::setX(int x)
	{
		this->_globalPosition.setX(x);
		this->_cursor->setPosition(this->_globalPosition.getX(),
			this->_globalPosition.getY() - (this->_cursor->getWidth() / 2));
		this->setValue(this->_value);
	}

	void	VSlider::setY(int y)
	{
		this->_globalPosition.setY(y);
		this->_cursor->setPosition(this->_globalPosition.getX(),
			this->_globalPosition.getY() - (this->_cursor->getWidth() / 2));
		this->setValue(this->_value);
	}

	void	VSlider::setLocalX(int x)
	{
		this->_localPosition.setX(x);
		this->_cursor->setLocalPosition(this->_localPosition.getX(),
			this->_localPosition.getY() - (this->_cursor->getWidth() / 2));
		this->setValue(this->_value);
	}

	void	VSlider::setLocalY(int y)
	{
		this->_localPosition.setY(y);
		this->_cursor->setLocalPosition(this->_localPosition.getX(),
			this->_localPosition.getY() - (this->_cursor->getWidth() / 2));
		this->setValue(this->_value);
	}
}