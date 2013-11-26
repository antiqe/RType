#ifndef _CONNECTION_CALLBACK_H_
# define _CONNECTION_CALLBACK_H_

#include "Widget.hpp"
#include "Event.hpp"

namespace Callback
{
	namespace Connection
	{
		void	connectOnClick(Engine::Widget* widget, Engine::Event* event);
		void	checkAvailability(Engine::Widget* widget, Engine::Event* event);
		void	checkAccess(Engine::Widget* widget, Engine::Event* event);
	}
}

#endif