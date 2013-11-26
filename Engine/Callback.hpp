#ifndef _CALLBACK_H_
# define _CALLBACK_H_

namespace Engine
{
	class Widget;
	class Event;

	namespace Callback
	{
		typedef void	(*EventFunction)(Widget*, Event*);
		void	quit(Widget*, Event*);
		void	followMouse(Engine::Widget*, Engine::Event*);

		typedef void*	(*ThreadFunction)(void*);
		void*	run(void* param);
	}
}

#endif
