#include "GameCallback.hpp"
#include "KeyboardEvent.hpp"
#include "Core.hpp"
#include "ScopeLock.hpp"
#include "GameState.hpp"
#include "NetworkEvent.hpp"

namespace Callback
{
	namespace Game
	{
		void	logicNetwork(Engine::Widget* widget, Engine::Event* event)
		{
			GameState*	state = dynamic_cast<GameState*>(widget);
			
			state->maj(dynamic_cast<Engine::NetworkEvent*>(event));
		}

		void	logicInput(Engine::Widget* widget, Engine::Event* event)
		{
			GameState*				state = dynamic_cast<GameState*>(widget);

			std::cout << dynamic_cast<Engine::KeyboardEvent*>(event)->getKeycode() << std::endl;
			if (event->getType() == Engine::KeyboardEvent::KEY_PRESSED)
				state->enableAction(dynamic_cast<Engine::KeyboardEvent*>(event));
			else
				state->disableAction(dynamic_cast<Engine::KeyboardEvent*>(event));
		}
	}
}
