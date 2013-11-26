#ifndef _LIST_BOX_CALLBACK_H_
# define _LIST_BOX_CALLBACK_H_

#include "Widget.hpp"
#include "Event.hpp"
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
			template <typename T>
			void	mouseWheel(Engine::Widget* widget, Engine::Event* event)
			{
				Engine::ListBox<T> *ListBox = dynamic_cast<Engine::ListBox<T>*>(widget);
				Engine::MouseEvent *mouseEvent = dynamic_cast<Engine::MouseEvent*>(event);

				if (ListBox->hit(mouseEvent->getX(), mouseEvent->getY()))
				{
					VSlider *slider = dynamic_cast<VSlider *>(ListBox->getChild(ListBox->getName()));
					slider->scroll(mouseEvent->getDelta());
				}
			}

			template <typename T>
			void	mouseClick(Engine::Widget* widget, Engine::Event* event)
			{
				Engine::ListBox<T> *ListBox = dynamic_cast< Engine::ListBox<T>*>(widget);
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

#endif