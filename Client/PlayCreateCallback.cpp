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
				Ultra::IMutex *mutex = Engine::Core::getInstance()->access(Engine::AModule::DATA);
				mutex->lock();
				DataModule *dm = dynamic_cast<DataModule*>(Engine::Core::getInstance()->getModule(Engine::AModule::DATA));
				dm->setAttr("id_room", Ultra::Value((unsigned short)id));
				mutex->unlock();
				PlayCreateState* state = dynamic_cast<PlayCreateState *>(widget);
				state->goToRoom();
			}
			else
			{
				PlayCreateState* state = dynamic_cast<PlayCreateState *>(widget);
				state->displayError("Can't connect to room");
			}
		}
	}
}