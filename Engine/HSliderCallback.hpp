#ifndef _H_SLIDER_CALLBACK_H_
# define _H_SLIDER_CALLBACK_H_

#include "Widget.hpp"
#include "Event.hpp"

namespace Engine
{
	namespace Callback
	{
		namespace HSlider
		{
			void	mouseClick(Engine::Widget* widget, Engine::Event* event);
			void	mouseWheel(Engine::Widget* widget, Engine::Event* event);
		}
	}
}
#endif