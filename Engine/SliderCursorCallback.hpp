#ifndef _SLIDER_CURSOR_CALLBACK_H_
# define _SLIDER_CURSOR_CALLBACK_H_

#include "Widget.hpp"
#include "Event.hpp"

namespace Engine
{
	namespace Callback
	{
		namespace SliderCursor
		{
			void	mouseOver(Engine::Widget* widget, Engine::Event* event);
			void	mouseClick(Engine::Widget* widget, Engine::Event* event);
			void	mouseMoveX(Engine::Widget* widget, Engine::Event* event);
			void	mouseMoveY(Engine::Widget* widget, Engine::Event* event);
		}
	}
}

#endif