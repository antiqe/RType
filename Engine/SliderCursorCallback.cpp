#include "SliderCursorCallback.hpp"
#include "Core.hpp"
#include "MouseEvent.hpp"
#include "SliderCursor.hpp"
#include "ASlider.hpp"

namespace Engine
{
	namespace Callback
	{
		namespace SliderCursor
		{
			void	mouseOver(Engine::Widget* widget, Engine::Event* event)
			{
				Engine::SliderCursor* SliderCursor = dynamic_cast< Engine::SliderCursor*>(widget);
				Engine::MouseEvent*	mouseEvent = dynamic_cast<Engine::MouseEvent*>(event);
				Engine::SliderCursor::Status status = SliderCursor->getStatus();

				if (status != Engine::SliderCursor::CLICKED)
				{
					if (SliderCursor->hit(mouseEvent->getX(), mouseEvent->getY()))
						SliderCursor->setStatus(Engine::SliderCursor::HOVER);
					else
						SliderCursor->setStatus(Engine::SliderCursor::NORMAL);
				}
			}

			void	mouseClick(Engine::Widget* widget, Engine::Event* event)
			{
				Engine::SliderCursor *SliderCursor = dynamic_cast< Engine::SliderCursor*>(widget);
				Engine::MouseEvent *mouseEvent = dynamic_cast<Engine::MouseEvent*>(event);

				if (SliderCursor->hit(mouseEvent->getX(), mouseEvent->getY()))
				{
					if (mouseEvent->isPressed())
						SliderCursor->setStatus(Engine::SliderCursor::CLICKED);
					else
						SliderCursor->setStatus(Engine::SliderCursor::HOVER);
				}
				else
					SliderCursor->setStatus(Engine::SliderCursor::NORMAL);
			}

			void mouseMoveX(Engine::Widget* widget, Engine::Event* event)
			{
				Engine::SliderCursor *SliderCursor = dynamic_cast< Engine::SliderCursor*>(widget);
				Engine::MouseEvent *mouseEvent = dynamic_cast<Engine::MouseEvent*>(event);

				if (SliderCursor->getStatus() == Engine::SliderCursor::CLICKED)
				{
					ASlider *parent = dynamic_cast<ASlider *>(SliderCursor->getParent());
					if (parent->hit(mouseEvent->getX(), SliderCursor->getParent()->getY()))
						parent->moveCursor(mouseEvent->getX());
				}
			}

			void mouseMoveY(Engine::Widget* widget, Engine::Event* event)
			{
				Engine::SliderCursor *SliderCursor = dynamic_cast< Engine::SliderCursor*>(widget);
				Engine::MouseEvent *mouseEvent = dynamic_cast<Engine::MouseEvent*>(event);

				if (SliderCursor->getStatus() == Engine::SliderCursor::CLICKED)
				{
					ASlider *parent = dynamic_cast<ASlider *>(SliderCursor->getParent());
					if (parent->hit(SliderCursor->getParent()->getX(), mouseEvent->getY()))
						parent->moveCursor(mouseEvent->getY());
				}
			}
		}
	}
}