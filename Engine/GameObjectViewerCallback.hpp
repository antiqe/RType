#ifndef _GAME_OBJECT_VIEWER_CALLBACK_H_
# define _GAME_OBJECT_VIEWER_CALLBACK_H_

namespace Engine
{
	class Widget;
	class Event;

	namespace Callback
	{
		namespace GameObjectViewer
		{
			void	nextOnClick(Widget*, Event*);
			void	prevOnClick(Widget*, Event*);
		}
	}
}

#endif
