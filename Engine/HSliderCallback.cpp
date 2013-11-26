#include "HSliderCallback.hpp"
#include "Core.hpp"
#include "MouseEvent.hpp"
#include "ASlider.hpp"

namespace Engine
{
	namespace Callback
	{
		namespace HSlider
		{
			void	mouseClick(Engine::Widget* widget, Engine::Event* event)
			{
				Engine::ASlider *Slider = dynamic_cast< Engine::ASlider*>(widget);
				Engine::MouseEvent *mouseEvent = dynamic_cast<Engine::MouseEvent*>(event);

				if (Slider->hit(mouseEvent->getX(), mouseEvent->getY()) && mouseEvent->isReleased())
					Slider->moveCursor(mouseEvent->getX());
			}

			void	mouseWheel(Engine::Widget* widget, Engine::Event* event)
			{
				Engine::ASlider *Slider = dynamic_cast< Engine::ASlider*>(widget);
				Engine::MouseEvent *mouseEvent = dynamic_cast<Engine::MouseEvent*>(event);

				if (Slider->hit(mouseEvent->getX(), mouseEvent->getY()))
					Slider->scroll(mouseEvent->getDelta());
			}
		}
	}
}
