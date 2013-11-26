#include "MouseEvent.hpp"

namespace Engine
{
	std::string const	MouseEvent::MIDDLE_CLICK = "middle click";
	std::string const	MouseEvent::RIGHT_CLICK = "right click";
	std::string const	MouseEvent::LEFT_CLICK = "left click";
	std::string const	MouseEvent::MOUSE_MOVE = "mouse move";
	std::string const	MouseEvent::MOUSE_WHEEL = "mouse wheel";

	MouseEvent::MouseEvent(std::string const& type, int x, int y, int delta)
		: Event(Event::MOUSE, type)
	{
		this->_attr["x"] = Ultra::Value(x);
		this->_attr["y"] = Ultra::Value(y);
		this->_attr["delta"] = Ultra::Value(delta);
		this->_attr["state"] = Ultra::Value(-1);
	}

	MouseEvent::MouseEvent(std::string const& type, int x, int y, bool state)
		: Event(Event::MOUSE, type)
	{
		this->_attr["x"] = Ultra::Value(x);
		this->_attr["y"] = Ultra::Value(y);
		this->_attr["delta"] = Ultra::Value(0);
		this->_attr["state"] = Ultra::Value((int)state);
	}

	MouseEvent::MouseEvent(std::string const& type, int x, int y)
		: Event(Event::MOUSE, type)
	{
		this->_attr["x"] = Ultra::Value(x);
		this->_attr["y"] = Ultra::Value(y);
		this->_attr["delta"] = Ultra::Value(0);
		this->_attr["state"] = Ultra::Value(-1);
	}

	MouseEvent::~MouseEvent()
	{

	}

	int	MouseEvent::getX() const
	{
		return (this->_attr.find("x")->second.as<int>());
	}

	int	MouseEvent::getY() const
	{
		return (this->_attr.find("y")->second.as<int>());
	}

	int		MouseEvent::getDelta() const
	{
		return (this->_attr.find("delta")->second.as<int>());
	}

	bool	MouseEvent::isPressed() const
	{
		Ultra::Value v = this->_attr.find("state")->second;

		return (v.as<int>() == -1 ? false : !(!v.as<int>()));
	}

	bool	MouseEvent::isReleased() const
	{
		Ultra::Value v = this->_attr.find("state")->second;

		return (v.as<int>() == -1 ? false : !v.as<int>());
	}

	void	MouseEvent::setX(int x)
	{
		this->_attr["x"] = Ultra::Value(x);
	}

	void	MouseEvent::setY(int y)
	{
		this->_attr["y"] =  Ultra::Value(y);
	}

	void	MouseEvent::setDelta(int delta)
	{
		this->_attr["delta"] =  Ultra::Value(delta);
	}

	void	MouseEvent::setState(bool state)
	{
		this->_attr["state"] =  Ultra::Value((int)state);
	}
}