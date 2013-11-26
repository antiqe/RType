#include "RoomStateCallback.hpp"
#include "RoomState.hpp"
#include "MouseEvent.hpp"
#include "Core.hpp"
#include "State.hpp"
#include "ScopeLock.hpp"

namespace Callback
{
	namespace Room
	{
		void	backOnClick(Engine::Widget* widget, Engine::Event* event)
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
					RoomState *state = dynamic_cast<RoomState *>(widget->getParent());
					state->quitRoom();
					button->setStatus(Engine::Button::NORMAL);
					Engine::AStateModule* stateModule = dynamic_cast<Engine::AStateModule*>(Engine::Core::getInstance()->getModule(Engine::AModule::STATE));
					Ultra::ScopeLock lock(Engine::Core::getInstance()->access(Engine::AModule::STATE));
					stateModule->pop();
				}
			}
			else
				button->setStatus(Engine::Button::NORMAL);
		}
	}
}