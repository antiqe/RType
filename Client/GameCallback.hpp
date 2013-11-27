#ifndef _GAME_CALLBACK_H_
# define _GAME_CALLBACK_H_

#include "Widget.hpp"
#include "Event.hpp"

namespace Callback
{
	namespace Game
	{
		void	logicNetwork(Engine::Widget* widget, Engine::Event* event);
		void	logicInput(Engine::Widget* widget, Engine::Event* event);
	}
}

#endif