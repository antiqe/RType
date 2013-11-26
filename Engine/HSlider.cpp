#include "HSlider.hpp"
#include "HSliderCallback.hpp"
#include "SliderCursorCallback.hpp"
#include "MouseEvent.hpp"

namespace Engine
{
	HSlider::HSlider(std::string const &name, std::string const &normalFile, 
		std::string const &cursorNormalFile, std::string const &cursorClickedFile,
		std::string const &cursorHoverFile, int min, int max, int defaultValue)
		: ASlider(name, normalFile, cursorNormalFile, cursorClickedFile, cursorHoverFile, 
		Callback::SliderCursor::mouseMoveX, min, max, defaultValue)
	{
	}

	HSlider::~HSlider()
	{
	}

	void	HSlider::initialize()
	{
		ASlider::initialize();
		this->addEventListener(Engine::Event::MOUSE, Engine::MouseEvent::LEFT_CLICK, &Callback::HSlider::mouseClick);
		this->addEventListener(Engine::Event::MOUSE, Engine::MouseEvent::MOUSE_WHEEL, &Callback::HSlider::mouseWheel);
		Widget::initialize();
	}

	void	HSlider::unload()
	{
		this->removeEventListener(Engine::Event::MOUSE, Engine::MouseEvent::MOUSE_MOVE);
		this->removeEventListener(Engine::Event::MOUSE, Engine::MouseEvent::MOUSE_WHEEL);
		Widget::unload();
	}

	void	HSlider::moveCursor(int x)
	{
		int v = (this->_max - this->_min);
		int d = this->getWidth();
		int hit = x - this->getX();
		int offset = this->getX() - (this->_cursor->getWidth() / 2);
		if (!hit)
			this->_cursor->setPosition(offset, this->_cursor->getY());
		else
		{
			int nextSlice = 1;
			int interval = (d / v);
			while (hit > nextSlice * interval)
				nextSlice++;
			int slice = nextSlice - 1;
			if (hit - slice * (d / v) > nextSlice * (d / v) - hit)
			{
				this->_cursor->setPosition(nextSlice * (d / v) + offset, this->_cursor->getY());
				this->_value = nextSlice;
			}
			else
			{
				this->_cursor->setPosition(slice * (d / v) + offset, this->_cursor->getY());
				this->_value = slice;
			}
		}
	}

	void	HSlider::setValue(int value)
	{
		this->_value = value;
		if (value == 0)
			this->moveCursor(this->getX());
		else
		{
			int sliceSize = this->getWidth() / (this->_max - this->_min);
			int target = this->_value - Ultra::Converter::abs<int>(this->_min);
			this->moveCursor(this->getX() + (target * sliceSize));
		}
	}

	void	HSlider::setWidth(size_t w)
	{
		this->_size.setX(w);
		this->_cursor->setSize(this->_size.getX() / 10, this->_size.getY() * 2);
		this->setValue(this->_value);
	}

	void	HSlider::setHeight(size_t h)
	{
		this->_size.setY(h);
		this->_cursor->setSize(this->_size.getX() / 10, this->_size.getY() * 2);
		this->setValue(this->_value);
	}

	void	HSlider::setX(int x)
	{
		this->_globalPosition.setX(x);
		this->_cursor->setPosition(this->_globalPosition.getX() - (this->_cursor->getWidth() / 2),
			this->_globalPosition.getY() - (this->_size.getY() / 2));
		this->setValue(this->_value);
	}

	void	HSlider::setY(int y)
	{
		this->_globalPosition.setY(y);
		this->_cursor->setPosition(this->_globalPosition.getX() - (this->_cursor->getWidth() / 2),
			this->_globalPosition.getY() - (this->_size.getY() / 2));
		this->setValue(this->_value);
	}

	void	HSlider::setLocalX(int x)
	{
		this->_localPosition.setX(x);
		this->_cursor->setPosition(this->_localPosition.getX() - (this->_cursor->getWidth() / 2),
			this->_localPosition.getY() - (this->_size.getY() / 2));
		this->setValue(this->_value);
	}

	void	HSlider::setLocalY(int y)
	{
		this->_localPosition.setY(y);
		this->_cursor->setPosition(this->_localPosition.getX() - (this->_cursor->getWidth() / 2),
			this->_localPosition.getY() - (this->_size.getY() / 2));
		this->setValue(this->_value);
	}
}