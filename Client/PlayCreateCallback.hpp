#ifndef _PLAY_CREATE_CALLBACK_H_
# define _PLAY_CREATE_CALLBACK_H_

#include "Widget.hpp"
#include "Event.hpp"

namespace Callback
{
	namespace PlayCreate
	{
		void	createOnClick(Engine::Widget* widget, Engine::Event* event);
		void	checkRoomState(Engine::Widget* widget, Engine::Event* event);
	}
}

#endif