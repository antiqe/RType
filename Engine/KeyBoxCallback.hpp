#ifndef _KEY_BOX_CALLBACK_H_
# define _KEY_BOX_CALLBACK_H_

#include "Widget.hpp"
#include "Event.hpp"

namespace Engine
{
	namespace Callback
	{
		namespace KeyBox
		{
			void	mouseOver(Engine::Widget* widget, Engine::Event* event);
			void	mouseClick(Engine::Widget* widget, Engine::Event* event);
			void	touchPressed(Engine::Widget* widget, Engine::Event* event);
			void	touchReleased(Engine::Widget* widget, Engine::Event* event);
		}
	}
}

#endif