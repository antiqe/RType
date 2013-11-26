#include <iostream>

#include "ListBoxCallback.hpp"
#include "Core.hpp"
#include "MouseEvent.hpp"
#include "ListBox.hpp"
#include "VSlider.hpp"

namespace Engine
{
	namespace Callback
	{
		namespace ListBox
		{
			void	mouseWheel(Engine::Widget* widget, Engine::Event* event)
			{
				Engine::ListBox *ListBox = dynamic_cast< Engine::ListBox*>(widget);
				Engine::MouseEvent *mouseEvent = dynamic_cast<Engine::MouseEvent*>(event);

				if (ListBox->hit(mouseEvent->getX(), mouseEvent->getY()))
				{
					VSlider *slider = dynamic_cast<VSlider *>(ListBox->getChild(ListBox->getName()));
					slider->scroll(mouseEvent->getDelta());
				}
			}

			void	mouseClick(Engine::Widget* widget, Engine::Event* event)
			{
				Engine::ListBox *ListBox = dynamic_cast< Engine::ListBox*>(widget);
				Engine::MouseEvent *mouseEvent = dynamic_cast<Engine::MouseEvent*>(event);

				if (ListBox->hit(mouseEvent->getX(), mouseEvent->getY()))
				{
					if (ListBox->getChild(ListBox->getName())->hit(mouseEvent->getX(), mouseEvent->getY()))
						return ;

					int sliceSize = ListBox->getHeight() / ListBox->getNbrLine();
					int hit = mouseEvent->getY() - ListBox->getY();
					int slice = 1;

					while (hit > (slice * sliceSize))
						slice++;
					ListBox->focus(slice - 1);
				}
				else
					ListBox->unfocus();
			}
		}
	}
}