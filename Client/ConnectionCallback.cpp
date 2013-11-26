#include "ConnectionCallback.hpp"
#include "ConnectionState.hpp"
#include "MouseEvent.hpp"
#include "StateAuth.hpp"
#include "Core.hpp"
#include "ScopeLock.hpp"

namespace Callback
{
	namespace Connection
	{
		void	connectOnClick(Engine::Widget* widget, Engine::Event* event)
		{
			Engine::Button* button = dynamic_cast<Engine::Button*>(widget);
			Engine::MouseEvent*	mouseEvent = dynamic_cast<Engine::MouseEvent*>(event);

			if (button->isLock())
				return ;
			if (button->hit(mouseEvent->getX(), mouseEvent->getY()))
			{
				if (mouseEvent->isPressed())
					button->setStatus(Engine::Button::CLICKED);
				else
				{
					button->setStatus(Engine::Button::HOVER);
					ConnectionState* state = dynamic_cast<ConnectionState *>(button->getParent());
					state->connect();
				}
			}
			else
				button->setStatus(Engine::Button::NORMAL);
		}

		void	checkAvailability(Engine::Widget* widget, Engine::Event* event)
		{
			ConnectionState* state = dynamic_cast<ConnectionState *>(widget);

			char availability = event->getAttr<char>("state");
			if (availability == Network::FREE)
				state->login();
			else
				state->displayError("Unvailable server !");
		}

		void	checkAccess(Engine::Widget* widget, Engine::Event* event)
		{
			ConnectionState* state = dynamic_cast<ConnectionState *>(widget);

			char availability = event->getAttr<char>("state");
			if (availability == Network::ACCEPT)
				state->play();
			else
				state->displayError("Username or password incorrect !");
		}
	}
}
