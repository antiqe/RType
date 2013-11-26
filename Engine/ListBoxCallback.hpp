#ifndef _LIST_BOX_CALLBACK_H_
# define _LIST_BOX_CALLBACK_H_

#include "Widget.hpp"
#include "Event.hpp"

namespace Engine
{
	namespace Callback
	{
		namespace ListBox
		{
			void	mouseWheel(Engine::Widget* widget, Engine::Event* event);
			void	mouseClick(Engine::Widget* widget, Engine::Event* event);
		}
	}
}

#endif