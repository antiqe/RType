#ifndef _BUTTONCALLBACK_H_
# define _BUTTONCALLBACK_H_

#include "Widget.hpp"
#include "Event.hpp"

namespace Engine
{
	namespace Callback
	{
		namespace Button
		{
			void	mouseOver(Engine::Widget* widget, Engine::Event* event);
			void	mouseClick(Engine::Widget* widget, Engine::Event* event);
			void	quit(Engine::Widget* widget, Engine::Event* event);
			void	back(Engine::Widget* widget, Engine::Event* event);
		}
	}
}

#endif