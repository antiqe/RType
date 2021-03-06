#ifndef _TEXTBOX_CALLBACK_H_
# define _TEXTBOX_CALLBACK_H_

#include "Widget.hpp"
#include "Event.hpp"

namespace Engine
{
	namespace Callback
	{
		namespace TextBox
		{
			void	mouseOver(Engine::Widget* widget, Engine::Event* event);
			void	mouseClick(Engine::Widget* widget, Engine::Event* event);
			void	touchPressed(Engine::Widget* widget, Engine::Event* event);
			void	touchReleased(Engine::Widget* widget, Engine::Event* event);
		}
	}
}

#endif