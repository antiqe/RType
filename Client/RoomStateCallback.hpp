#ifndef _ROOM_STATE_CALLBACK_H_
# define _ROOM_STATE_CALLBACK_H_

#include "Widget.hpp"
#include "Event.hpp"

namespace Callback
{
	namespace Room
	{
		void	backOnClick(Engine::Widget* widget, Engine::Event* event);
		void	sendOnClick(Engine::Widget* widget, Engine::Event* event);
		void	onReceiveTalk(Engine::Widget* widget, Engine::Event* event);
		void	onRoomPlayerInfo(Engine::Widget* widget, Engine::Event* event);
	}
}

#endif