#include "RoomStateCallback.hpp"
#include "RoomState.hpp"
#include "MouseEvent.hpp"
#include "Core.hpp"
#include "State.hpp"
#include "CheckBoxCallback.hpp"
#include "StatePlayer.hpp"
#include "ScopeLock.hpp"

namespace Callback
{
	namespace Room
	{
			
		void	onKickEvent(Engine::Widget *widget, Engine::Event *event)
		{
			Engine::AStateModule* stateModule = dynamic_cast<Engine::AStateModule*>(Engine::Core::getInstance()->getModule(Engine::AModule::STATE));
			Ultra::ScopeLock lock(Engine::Core::getInstance()->access(Engine::AModule::STATE));
			stateModule->pop();
		}

		void	onGameStart(Engine::Widget *widget, Engine::Event *event)
		{
			Engine::AStateModule* stateModule = dynamic_cast<Engine::AStateModule*>(Engine::Core::getInstance()->getModule(Engine::AModule::STATE));
			Ultra::ScopeLock lock(Engine::Core::getInstance()->access(Engine::AModule::STATE));
			stateModule->push(State::GAME);
		}

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
					RoomState *state = dynamic_cast<RoomState *>(widget->getParent());
					state->sendStartRoom();
					button->setStatus(Engine::Button::NORMAL);
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
			if (go->isLock())
				go->unlock();
			else
				go->lock();
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

		
	  void	onPlayerReady(Engine::Widget *widget, Engine::Event *event)
	  {
		  Engine::CheckBox* button = dynamic_cast< Engine::CheckBox*>(widget);
		  Engine::MouseEvent*	mouseEvent = dynamic_cast<Engine::MouseEvent*>(event);

			if (button->isHidden())
				return ;
			if (button->hit(mouseEvent->getX(), mouseEvent->getY()))
			{
				if (mouseEvent->isPressed())
				{
					  Ultra::IMutex *mutex = Engine::Core::getInstance()->access(Engine::AModule::DATA);
					  mutex->lock();
					  DataModule *dm = dynamic_cast<DataModule*>(Engine::Core::getInstance()->getModule(Engine::AModule::DATA));
					  char statePlayer = dm->getAttr<char>("statePlayer");
					  std::stringstream ss;
					  dm->setAttr("statePlayer", Ultra::Value((char)((statePlayer == Network::READY)?Network::NONE:Network::READY)));
					  mutex->unlock();
					  RoomState *state = dynamic_cast<RoomState *>(widget->getParent()->getParent());
					  state->sendPlayerInfo();
					  button->toggle();
				}
			}
	  }

	  void	onRoomPlayerInfo(Engine::Widget* widget, Engine::Event* event)
		{
			std::string name = event->getAttr<std::string>("name");
			char id_player = (char)event->getAttr<char>("id_player");
			char specState = event->getAttr<char>("stateSpec");
			char pstate = event->getAttr<char>("state");

			std::cout << "PLAYER INFO [ID=" << (int)id_player << "] [NAME=" << name << "] " << std::endl;

			RoomState *state = dynamic_cast<RoomState *>(widget);
			std::stringstream ss;
			ss << (int)id_player;
			Engine::Widget * wpl = state->getChild("player" + ss.str());
			Engine::Widget * wcb = wpl->getChild("ready" + ss.str());
			Engine::CheckBox *cb = dynamic_cast<Engine::CheckBox *>(wcb);
			Player *pl = dynamic_cast<Player *>(wpl);


			Ultra::IMutex *mutex = Engine::Core::getInstance()->access(Engine::AModule::DATA);
			mutex->lock();
			DataModule *dm = dynamic_cast<DataModule*>(Engine::Core::getInstance()->getModule(Engine::AModule::DATA));
			std::string login = dm->getAttr<std::string>("login");
			if (login == name)
			{
				dm->setAttr("id_player", Ultra::Value((char)id_player));
				dm->setAttr("id_ship", Ultra::Value((char)event->getAttr<char>("id_ship")));
				char stateSpec = event->getAttr<char>("stateSpec");
				dm->setAttr("stateSpec", Ultra::Value((char)stateSpec));
				if (pl->isHidden())
				{
					
					cb->addEventListener(Engine::Event::MOUSE, Engine::MouseEvent::LEFT_CLICK, &onPlayerReady);
					cb->addEventListener(Engine::Event::MOUSE, Engine::MouseEvent::MOUSE_MOVE, &Engine::Callback::CheckBox::mouseOver);
					pl->show();
					//cb->show();
				}
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
			{
				mutex->unlock();
				if (pstate == Network::LEFT)
				{
					pl->hide();
					//cb->hide();
				}
				else
				{
					if (pl->isHidden())
					{
						pl->show();
					}
					else
					{
						if (!cb->isChecked() && pstate == Network::READY)
							cb->toggle();
						else if (cb->isChecked() && pstate == Network::NONE)
							cb->toggle();
					}
				}
			}
		}
	  }
}
