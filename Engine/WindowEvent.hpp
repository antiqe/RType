#ifndef _WINDOWEVENT_H_
# define _WINDOWEVENT_H_

#include <sys/types.h>
#include <string>

#include "Event.hpp"

namespace Engine
{
	class WindowEvent : public Event
	{
	public:
		WindowEvent(std::string const& type);
		virtual ~WindowEvent();

		static std::string const	CLOSED;
		static std::string const	LOST_FOCUS;
		static std::string const	GAINED_FOCUS;
	};
}

#endif
