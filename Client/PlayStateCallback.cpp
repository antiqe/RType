#include "PlayStateCallback.hpp"
#include "PlayState.hpp"
#include "MouseEvent.hpp"
#include "Core.hpp"
#include "State.hpp"
#include "ScopeLock.hpp"
#include "NetworkModule.hpp"

namespace Callback
{
	namespace PlayState
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
					button->setStatus(Engine::Button::HOVER);
					Engine::AStateModule* stateModule = dynamic_cast<Engine::AStateModule*>(Engine::Core::getInstance()->getModule(Engine::AModule::STATE));
					Ultra::IMutex* mutex = Engine::Core::getInstance()->access(Engine::AModule::NETWORK);
					mutex->lock();
					NetworkModule *net = dynamic_cast<NetworkModule*>(Engine::Core::getInstance()->getModule(Engine::AModule::NETWORK));
					net->stop();
					mutex->unlock();
					mutex = Engine::Core::getInstance()->access(Engine::AModule::STATE);
					mutex->lock();
					stateModule->popTo(State::CONNECTION);
					mutex->unlock();
				}
			}
			else
				button->setStatus(Engine::Button::NORMAL);
		}
	}
}