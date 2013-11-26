#include "CheckBoxCallback.hpp"
#include "Core.hpp"
#include "MouseEvent.hpp"
#include "CheckBox.hpp"

namespace Engine
{
	namespace Callback
	{
		namespace CheckBox
		{
			void	mouseOver(Engine::Widget* widget, Engine::Event* event)
			{
				Engine::CheckBox* CheckBox = dynamic_cast< Engine::CheckBox*>(widget);
				Engine::MouseEvent*	mouseEvent = dynamic_cast<Engine::MouseEvent*>(event);
				Engine::CheckBox::Status status = CheckBox->getStatus();

				if (status != Engine::CheckBox::CHECKED_CLICKED
					&& status != Engine::CheckBox::UNCHECKED_CLICKED)
				{
					Engine::CheckBox::Status statusStart = (status < Engine::CheckBox::UNCHECKED_NORMAL ?
						Engine::CheckBox::CHECKED_NORMAL : Engine::CheckBox::UNCHECKED_NORMAL);

					if (CheckBox->hit(mouseEvent->getX(), mouseEvent->getY()))
						CheckBox->setStatus(static_cast< Engine::CheckBox::Status>(Engine::CheckBox::CHECKED_HOVER + statusStart));
					else
						CheckBox->setStatus(statusStart);
				}
			}

			void	mouseClick(Engine::Widget* widget, Engine::Event* event)
			{
				Engine::CheckBox *CheckBox = dynamic_cast< Engine::CheckBox*>(widget);
				Engine::MouseEvent *mouseEvent = dynamic_cast<Engine::MouseEvent*>(event);
				Engine::CheckBox::Status statusStart = (CheckBox->getStatus() < Engine::CheckBox::UNCHECKED_NORMAL ?
					Engine::CheckBox::CHECKED_NORMAL : Engine::CheckBox::UNCHECKED_NORMAL);

				if (CheckBox->hit(mouseEvent->getX(), mouseEvent->getY()))
				{
					if (mouseEvent->isPressed())
						CheckBox->setStatus(static_cast< Engine::CheckBox::Status>(Engine::CheckBox::CHECKED_CLICKED + statusStart));
					else
					{
						statusStart = (statusStart == Engine::CheckBox::CHECKED_NORMAL ?
							Engine::CheckBox::UNCHECKED_NORMAL : Engine::CheckBox::CHECKED_NORMAL);
						CheckBox->setStatus(static_cast< Engine::CheckBox::Status>(Engine::CheckBox::CHECKED_HOVER + statusStart));
						CheckBox->toggle();
					}
				}
				else
					CheckBox->setStatus(statusStart);
			}
		}
	}
}