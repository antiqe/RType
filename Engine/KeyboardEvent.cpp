#include "KeyboardEvent.hpp"

namespace Engine
{
	const std::string	KeyboardEvent::KEY_PRESSED = "key pressed";
	const std::string	KeyboardEvent::KEY_RELEASED = "key released";

	KeyboardEvent::KeyboardEvent(std::string const& type, size_t keycode, bool ctrl, bool alt, bool shift)
		: Event(Event::KEYBOARD, type)
	{
		this->_attr["keycode"] = Ultra::Value(keycode);
		this->_attr["ctrl"] = Ultra::Value(ctrl);
		this->_attr["alt"] = Ultra::Value(alt);
		this->_attr["shift"] = Ultra::Value(shift);
	}

	KeyboardEvent::~KeyboardEvent()
	{

	}

	void	KeyboardEvent::setKeycode(size_t keycode)
	{
		this->_attr["keycode"] = Ultra::Value(keycode);
	}

	void	KeyboardEvent::setCtrl(bool ctrl)
	{
		this->_attr["ctrl"] = Ultra::Value(ctrl);
	}

	void	KeyboardEvent::setAlt(bool alt)
	{
		this->_attr["alt"] = Ultra::Value(alt);
	}

	void	KeyboardEvent::setShift(bool shift)
	{
		this->_attr["shift"] = Ultra::Value(shift);
	}

	size_t	KeyboardEvent::getKeycode() const
	{
		return (this->_attr.find("keycode")->second.as<size_t>());
	}

	bool	KeyboardEvent::isCtrlPressed() const
	{
		return (this->_attr.find("ctrl")->second.as<bool>());
	}

	bool	KeyboardEvent::isAltPressed() const
	{
		return (this->_attr.find("alt")->second.as<bool>());
	}

	bool	KeyboardEvent::isShiftPressed() const
	{
		return (this->_attr.find("shift")->second.as<bool>());
	}
}