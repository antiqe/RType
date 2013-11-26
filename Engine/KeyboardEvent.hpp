#ifndef _KEYBOARDEVENT_H_
# define _KEYBOARDEVENT_H_

#include <sys/types.h>
#include <string>

#include "Event.hpp"

namespace Engine
{
	class KeyboardEvent : public Event
	{
	public:
		KeyboardEvent(std::string const& type, size_t keycode = 0, bool ctrl = false, bool alt = false, bool shift = false);
		virtual ~KeyboardEvent();

		void		setKeycode(size_t keycode);
		void		setCtrl(bool ctrl);
		void		setAlt(bool alt);
		void		setShift(bool shift);

		size_t		getKeycode() const;
		bool		isCtrlPressed() const;
		bool		isAltPressed() const;
		bool		isShiftPressed() const;

		static std::string const	KEY_PRESSED;
		static std::string const	KEY_RELEASED;
	};
}

#endif
