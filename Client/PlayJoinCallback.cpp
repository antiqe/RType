#include <sstream>

#include "PlayJoinCallback.hpp"
#include "PlayJoinState.hpp"
#include "MouseEvent.hpp"
#include "Core.hpp"
#include "State.hpp"
#include "ScopeLock.hpp"
#include "NetworkModule.hpp"
#include "RoomInfo.hpp"

namespace Callback
{
	namespace PlayJoin
	{
		void getRoomInfo(Engine::Widget* widget, Engine::Event* event)
		{
			std::stringstream ss;

			PlayJoinState *state = dynamic_cast<PlayJoinState *>(widget);
			Engine::Widget * wlb = state->getChild("list");
			Engine::ListBox *lb = dynamic_cast<Engine::ListBox *>(wlb);
			unsigned short id = event->getAttr<unsigned short>("id");
			std::string name = event->getAttr<std::string>("name");
			bool priv = event->getAttr<bool>("private");
			int cur_player = event->getAttr<char>("cur_player");
			int max_player = event->getAttr<char>("max_player");

			RoomInfo *iroom = new RoomInfo(id, name, priv, cur_player, max_player);
			lb->push(iroom->toString(), iroom);
		}

		void refreshOnClick(Engine::Widget* widget, Engine::Event* event)
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
					PlayJoinState *state = dynamic_cast<PlayJoinState *>(widget->getParent());
					state->refresh();
					button->setStatus(Engine::Button::NORMAL);
				}
			}
			else
				button->setStatus(Engine::Button::NORMAL);
		}
		
		void selectOnClick(Engine::Widget* widget, Engine::Event* event)
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
					PlayJoinState *state = dynamic_cast<PlayJoinState *>(widget->getParent());
					state->selectServer();
					button->setStatus(Engine::Button::NORMAL);
				}
			}
			else
				button->setStatus(Engine::Button::NORMAL);
		}
	}
}