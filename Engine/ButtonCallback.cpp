#include "ButtonCallback.hpp"
#include "Core.hpp"
#include "MouseEvent.hpp"
#include "Button.hpp"
#include "ScopeLock.hpp"

namespace Engine
{
	namespace Callback
	{
		namespace Button
		{
			void	mouseOver(Engine::Widget* widget, Engine::Event* event)
			{
				Engine::Button* button = dynamic_cast< Engine::Button*>(widget);
				Engine::MouseEvent*	mouseEvent = dynamic_cast<Engine::MouseEvent*>(event);

				if (!button->isLock())
					if (button->getStatus() != Engine::Button::CLICKED)
					{

						if (button->hit(mouseEvent->getX(), mouseEvent->getY()))
							button->setStatus(Engine::Button::HOVER);
						else
							button->setStatus(Engine::Button::NORMAL);
					}
			}

			void	mouseClick(Engine::Widget* widget, Engine::Event* event)
			{
				Engine::Button* button = dynamic_cast< Engine::Button*>(widget);
				Engine::MouseEvent*	mouseEvent = dynamic_cast<Engine::MouseEvent*>(event);

				if (!button->isLock())
				{
					if (button->hit(mouseEvent->getX(), mouseEvent->getY()))
					{
						if (mouseEvent->isPressed())
							button->setStatus(Engine::Button::CLICKED);
						else
						{
							button->setStatus(Engine::Button::HOVER);
							button->active();
						}
					}
					else
						button->setStatus(Engine::Button::NORMAL);
				}
			}

			void	quit(Engine::Widget* widget, Engine::Event* event)
			{
				Engine::Button* button = dynamic_cast< Engine::Button*>(widget);
				Engine::MouseEvent*	mouseEvent = dynamic_cast<Engine::MouseEvent*>(event);

				if (button->hit(mouseEvent->getX(), mouseEvent->getY()))
				{
					if (mouseEvent->isPressed())
						button->setStatus(Engine::Button::CLICKED);
					else
					{
						button->setStatus(Engine::Button::HOVER);
						Engine::Callback::quit(widget, event);
					}
				}
				else
					button->setStatus(Engine::Button::NORMAL);
			}

			void	back(Engine::Widget* widget, Engine::Event* event)
			{
				Engine::Button* button = dynamic_cast< Engine::Button*>(widget);
				Engine::MouseEvent*	mouseEvent = dynamic_cast<Engine::MouseEvent*>(event);

				if (button->hit(mouseEvent->getX(), mouseEvent->getY()))
				{
					if (mouseEvent->isPressed())
						button->setStatus(Engine::Button::CLICKED);
					else
					{
						button->setStatus(Engine::Button::HOVER);
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
}