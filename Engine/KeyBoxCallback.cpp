#include "KeyBoxCallback.hpp"
#include "Core.hpp"
#include "MouseEvent.hpp"
#include "KeyboardEvent.hpp"
#include "KeyBox.hpp"

namespace Engine
{
	namespace Callback
	{
		namespace KeyBox
		{
			void	mouseOver(Engine::Widget* widget, Engine::Event* event)
			{
				Engine::KeyBox* KeyBox = dynamic_cast< Engine::KeyBox*>(widget);
				Engine::MouseEvent*	mouseEvent = dynamic_cast<Engine::MouseEvent*>(event);

				if (!KeyBox->isLocked() && KeyBox->getStatus() != Engine::KeyBox::SELECTED)
				{
					if (KeyBox->hit(mouseEvent->getX(), mouseEvent->getY()))
						KeyBox->setStatus(Engine::KeyBox::HOVER);
					else
						KeyBox->setStatus(Engine::KeyBox::NORMAL);
				}
			}

			void	mouseClick(Engine::Widget* widget, Engine::Event* event)
			{
				Engine::KeyBox* KeyBox = dynamic_cast< Engine::KeyBox*>(widget);
				Engine::MouseEvent*	mouseEvent = dynamic_cast<Engine::MouseEvent*>(event);

				if (!KeyBox->isLocked() && KeyBox->hit(mouseEvent->getX(), mouseEvent->getY()))
				{
					if (mouseEvent->isPressed())
					{
						if (KeyBox->getStatus() != Engine::KeyBox::SELECTED)
						{
							KeyBox->setStatus(Engine::KeyBox::SELECTED);
							KeyBox->setText("<???>");
						}
						else
							KeyBox->setStatus(Engine::KeyBox::HOVER);
					}
				}
				else
					KeyBox->setStatus(Engine::KeyBox::NORMAL);
			}

			void	touchPressed(Engine::Widget* widget, Engine::Event* event)
			{
				Engine::KeyBox*	KeyBox = dynamic_cast< Engine::KeyBox*>(widget);
				Engine::KeyboardEvent*	keyboardEvent = dynamic_cast<Engine::KeyboardEvent*>(event);

				if (!KeyBox->isLocked() && KeyBox->getStatus() == Engine::KeyBox::SELECTED)
				{
					if (keyboardEvent->getKeycode() == Engine::Keyboard::Return)
						KeyBox->setText("<Enter>");
					else if (keyboardEvent->getKeycode() == Engine::Keyboard::Up)
						KeyBox->setText("<Up>");
					else if (keyboardEvent->getKeycode() == Engine::Keyboard::Down)
						KeyBox->setText("<Down>");
					else if (keyboardEvent->getKeycode() == Engine::Keyboard::Left)
						KeyBox->setText("<Left>");
					else if (keyboardEvent->getKeycode() == Engine::Keyboard::Right)
						KeyBox->setText("<Right>");
					else
						KeyBox->addCharacter(static_cast<Engine::Keyboard::Key>(keyboardEvent->getKeycode()));
				}
			}

			void	touchReleased(Engine::Widget* widget, Engine::Event* event)
			{
				Engine::KeyBox*	KeyBox = dynamic_cast< Engine::KeyBox*>(widget);
				Engine::KeyboardEvent*	keyboardEvent = dynamic_cast<Engine::KeyboardEvent*>(event);

				if (!KeyBox->isLocked() && KeyBox->getStatus() == Engine::KeyBox::SELECTED)
					KeyBox->setStatus(Engine::KeyBox::NORMAL);
			}
		}
	}
}