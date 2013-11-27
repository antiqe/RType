#include "RoomStateCallback.hpp"
#include "RoomState.hpp"
#include "MouseEvent.hpp"
#include "Core.hpp"
#include "State.hpp"
#include "StatePlayer.hpp"
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

		void	goOnClick(Engine::Widget* widget, Engine::Event* event)
		{
			
			Engine::Button* button = dynamic_cast< Engine::Button*>(widget);
			Engine::MouseEvent*	mouseEvent = dynamic_cast<Engine::MouseEvent*>(event);

			if (button->isHidden())
				return ;
			if (button->isLock())
				return ;
			if (button->hit(mouseEvent->getX(), mouseEvent->getY()))
			{
				if (mouseEvent->isPressed())
					button->setStatus(Engine::Button::CLICKED);
				else
				{
					button->active();
				}
			}
			else
				button->setStatus(Engine::Button::NORMAL);
		}

		void	onRoomStart(Engine::Widget* widget, Engine::Event* event)
		{
			RoomState *state = dynamic_cast<RoomState *>(widget);
			Engine::Widget * wb = state->getChild("go");
			Engine::Button *go = dynamic_cast<Engine::Button *>(wb);
			go->unlock();
		}

		void	onReceiveTalk(Engine::Widget* widget, Engine::Event* event)
		{
			RoomState *state = dynamic_cast<RoomState *>(widget);
			Engine::Widget * wlb = state->getChild("chatBox");
			Engine::ListBox<> *lb = dynamic_cast<Engine::ListBox<> *>(wlb);
			std::string from = event->getAttr<std::string>("from");
			std::string msg = event->getAttr<std::string>("msg");
			lb->push(from + " : " + msg, 0, true);
		}

	  void	onRoomPlayerInfo(Engine::Widget* widget, Engine::Event* event)
		{
			std::string name = event->getAttr<std::string>("name");
			char specState = event->getAttr<char>("stateSpec");
			std::cout << "===> Player Info [" << name << "] [" << ((specState == Network::MASTER) ? "MASTER" : "SIMPLE") << "] <====" << std::endl;

			Ultra::IMutex *mutex = Engine::Core::getInstance()->access(Engine::AModule::DATA);
			mutex->lock();
			DataModule *dm = dynamic_cast<DataModule*>(Engine::Core::getInstance()->getModule(Engine::AModule::DATA));
			std::string login = dm->getAttr<std::string>("login");
			if (login == name)
			{
				dm->setAttr("id_player", Ultra::Value((char)event->getAttr<char>("id_player")));
				dm->setAttr("id_ship", Ultra::Value((char)event->getAttr<char>("id_ship")));
				char stateSpec = event->getAttr<char>("stateSpec");
				dm->setAttr("stateSpec", Ultra::Value((char)stateSpec));
				if (stateSpec == Network::MASTER)
				{
					RoomState *state = dynamic_cast<RoomState *>(widget);
					Engine::Widget * wb = state->getChild("go");
					Engine::Button *go = dynamic_cast<Engine::Button *>(wb);
					go->show();
				}
				mutex->unlock();
			}
			else
				mutex->unlock();
		}
	}
}
