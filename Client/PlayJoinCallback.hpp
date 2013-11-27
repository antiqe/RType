#ifndef _PLAY_JOIN_CALLBACK_H_
# define _PLAY_JOIN_CALLBACK_H_

#include "Widget.hpp"
#include "Event.hpp"

namespace Callback
{
	namespace PlayJoin
	{
		void getRoomInfo(Engine::Widget* widget, Engine::Event* event);
		void refreshOnClick(Engine::Widget* widget, Engine::Event* event);
		void selectOnClick(Engine::Widget* widget, Engine::Event* event);
		void onRoomState(Engine::Widget* widget, Engine::Event* event);
	}
}

#endif