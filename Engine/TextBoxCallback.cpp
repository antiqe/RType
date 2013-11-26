#include "TextBoxCallback.hpp"
#include "Core.hpp"
#include "MouseEvent.hpp"
#include "KeyboardEvent.hpp"
#include "TextBox.hpp"

namespace Engine
{
	namespace Callback
	{
		namespace TextBox
		{
			static int x = 0;
			static int y = 0;

			void	mouseOver(Engine::Widget* widget, Engine::Event* event)
			{
				Engine::TextBox* textBox = dynamic_cast< Engine::TextBox*>(widget);
				Engine::MouseEvent*	mouseEvent = dynamic_cast<Engine::MouseEvent*>(event);

				if (!textBox->isLocked() && textBox->getStatus() != Engine::TextBox::SELECTED)
				{
					if (textBox->hit(mouseEvent->getX(), mouseEvent->getY()))
						textBox->setStatus(Engine::TextBox::HOVER);
					else
						textBox->setStatus(Engine::TextBox::NORMAL);
				}
				x = mouseEvent->getX();
				y = mouseEvent->getY();
			}

			void	mouseClick(Engine::Widget* widget, Engine::Event* event)
			{
				Engine::TextBox* textBox = dynamic_cast< Engine::TextBox*>(widget);
				Engine::MouseEvent*	mouseEvent = dynamic_cast<Engine::MouseEvent*>(event);

				if (!textBox->isLocked() && textBox->hit(mouseEvent->getX(), mouseEvent->getY()))
				{
					if (mouseEvent->isPressed())
					{
						if (textBox->getStatus() != Engine::TextBox::SELECTED)
							textBox->setStatus(Engine::TextBox::SELECTED);
						else
							textBox->setStatus(Engine::TextBox::HOVER);
					}
				}
				else
					textBox->setStatus(Engine::TextBox::NORMAL);
				x = mouseEvent->getX();
				y = mouseEvent->getY();
			}

			void	touchPressed(Engine::Widget* widget, Engine::Event* event)
			{
				Engine::TextBox*	textBox = dynamic_cast< Engine::TextBox*>(widget);
				Engine::KeyboardEvent*	keyboardEvent = dynamic_cast<Engine::KeyboardEvent*>(event);

				if (!textBox->isLocked() && textBox->getStatus() == Engine::TextBox::SELECTED)
				{
					if (keyboardEvent->getKeycode() == Engine::Keyboard::Return)
						textBox->setStatus(textBox->hit(x, y) ? Engine::TextBox::HOVER : Engine::TextBox::NORMAL);
					else if (keyboardEvent->getKeycode() == Engine::Keyboard::BackSpace)
						textBox->delCharacter();
					else
						textBox->addCharacter(static_cast<Engine::Keyboard::Key>(keyboardEvent->getKeycode()));
					textBox->setKeyPressed(static_cast<Engine::Keyboard::Key>(keyboardEvent->getKeycode()));
				}
			}

			void	touchReleased(Engine::Widget* widget, Engine::Event* event)
			{
				Engine::TextBox*	textBox= dynamic_cast< Engine::TextBox*>(widget);
				Engine::KeyboardEvent*	keyboardEvent= dynamic_cast<Engine::KeyboardEvent*>(event);

				if (!textBox->isLocked() && textBox->getStatus() == Engine::TextBox::SELECTED)
					textBox->setKeyReleased(static_cast<Engine::Keyboard::Key>(keyboardEvent->getKeycode()));
			}
		}
	}
}