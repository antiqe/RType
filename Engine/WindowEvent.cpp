#include "WindowEvent.hpp"

namespace Engine
{
	const std::string	WindowEvent::CLOSED = "closed";
	const std::string	WindowEvent::LOST_FOCUS = "lost focus";
	const std::string	WindowEvent::GAINED_FOCUS = "gained focus";

	WindowEvent::WindowEvent(std::string const& type)
		: Event(Event::WINDOW, type)
	{

	}

	WindowEvent::~WindowEvent()
	{

	}
}