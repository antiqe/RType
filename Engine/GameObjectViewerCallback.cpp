#include "Callback.hpp"
#include "AModule.hpp"
#include "Core.hpp"
#include "ScopeLock.hpp"
#include "MouseEvent.hpp"
#include "Widget.hpp"
#include "Button.hpp"
#include "GameObjectViewer.hpp"

namespace Engine
{
	namespace Callback
	{
		namespace GameObjectViewer
		{
			void	nextOnClick(Engine::Widget* widget, Engine::Event* event)
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
						Engine::GameObjectViewer* parent = dynamic_cast<Engine::GameObjectViewer*>(button->getParent());
						parent->next();
					}
				}
				else
					button->setStatus(Engine::Button::NORMAL);
			}

			void	prevOnClick(Engine::Widget* widget, Engine::Event* event)
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
						Engine::GameObjectViewer* parent = dynamic_cast<Engine::GameObjectViewer*>(button->getParent());
						parent->prev();
					}
				}
				else
					button->setStatus(Engine::Button::NORMAL);
			}
		}
	}
}