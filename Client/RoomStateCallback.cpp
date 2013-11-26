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

		void	sendOnClick(Engine::Widget* widget, Engine::Event* event)
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
					state->roomTalk();
					button->setStatus(Engine::Button::NORMAL);
				}
			}
			else
				button->setStatus(Engine::Button::NORMAL);
		}

		void	onReceiveTalk(Engine::Widget* widget, Engine::Event* event)
		{
			RoomState *state = dynamic_cast<RoomState *>(widget);
			Engine::Widget * wlb = state->getChild("chatBox");
			Engine::ListBox<> *lb = dynamic_cast<Engine::ListBox<> *>(wlb);
			std::string from = event->getAttr<std::string>("from");
			std::string msg = event->getAttr<std::string>("msg");
			lb->push(from + " : " + msg, 0);
		}
	}
}