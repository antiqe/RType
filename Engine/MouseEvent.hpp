#ifndef _MOUSEEVENT_H_
# define _MOUSEEVENT_H_

#include <string>

#include "Event.hpp"

namespace Engine
{
	class MouseEvent : public Event
	{
	public:
		MouseEvent(std::string const& type, int x, int y, int delta);
		MouseEvent(std::string const& type, int x, int y, bool state);
		MouseEvent(std::string const& type, int x, int y);
		virtual ~MouseEvent();

		int		getX() const;
		int		getY() const;
		int		getDelta() const;
		bool	isPressed() const;
		bool	isReleased() const;

		void	setX(int x);
		void	setY(int y);
		void	setDelta(int delta);
		void	setState(bool state);

		static std::string const	MIDDLE_CLICK;
		static std::string const	RIGHT_CLICK;
		static std::string const	LEFT_CLICK;
		static std::string const	MOUSE_WHEEL;
		static std::string const	MOUSE_MOVE;
	};
}

#endif