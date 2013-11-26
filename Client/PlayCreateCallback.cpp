#include "PlayCreateCallback.hpp"
#include "PlayCreateState.hpp"
#include "MouseEvent.hpp"
#include "Core.hpp"
#include "ScopeLock.hpp"
#include "StateRoom.hpp"

namespace Callback
{
	namespace PlayCreate
	{
		void	createOnClick(Engine::Widget* widget, Engine::Event* event)
		{
			Engine::Button* button = dynamic_cast< Engine::Button*>(widget);
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
					PlayCreateState* state = dynamic_cast<PlayCreateState *>(button->getParent());
					state->createRoom();
				}
			}
			else
				button->setStatus(Engine::Button::NORMAL);
		}

		void	checkRoomState(Engine::Widget* widget, Engine::Event* event)
		{
			unsigned short id = event->getAttr<unsigned short>("id");
			char status = event->getAttr<char>("state");

			if (status == Network::OK)
			{
				PlayCreateState* state = dynamic_cast<PlayCreateState *>(widget);
				state->goToRoom();
			}
			else
			{
				PlayCreateState* state = dynamic_cast<PlayCreateState *>(widget);
				state->displayError("Can't connect to room");
			}
			std::cout << "Join room id = " << id << std::endl;
			std::cout << "State room = " << (int)status << std::endl;
		}
	}
}