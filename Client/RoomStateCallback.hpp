#ifndef _ROOM_STATE_CALLBACK_H_
# define _ROOM_STATE_CALLBACK_H_

#include "Widget.hpp"
#include "Event.hpp"

namespace Callback
{
	namespace Room
	{
		void	backOnClick(Engine::Widget* widget, Engine::Event* event);
		void	goOnClick(Engine::Widget* widget, Engine::Event* event);
		void	sendOnClick(Engine::Widget* widget, Engine::Event* event);
		void	onReceiveTalk(Engine::Widget* widget, Engine::Event* event);
		void	onRoomPlayerInfo(Engine::Widget* widget, Engine::Event* event);
		void	onRoomStart(Engine::Widget *widget, Engine::Event *event);
		void	onPlayerReady(Engine::Widget *widget, Engine::Event *event);
		void	onKickEvent(Engine::Widget *widget, Engine::Event *event);
		void	onGameStart(Engine::Widget *widget, Engine::Event *event);
		void	onNextClick(Engine::Widget *widget, Engine::Event *event);
		void	onPrevClick(Engine::Widget *widget, Engine::Event *event);
	}
}

#endif