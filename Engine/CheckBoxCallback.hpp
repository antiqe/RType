#ifndef _CHECK_BOX_CALLBACK_H_
# define _CHECK_BOX_CALLBACK_H_

#include "Widget.hpp"
#include "Event.hpp"

namespace Engine
{
	namespace Callback
	{
		namespace CheckBox
		{
			void	mouseOver(Engine::Widget* widget, Engine::Event* event);
			void	mouseClick(Engine::Widget* widget, Engine::Event* event);
		}
	}
}

#endif