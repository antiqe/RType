#ifndef _EVENTMODULE_H_
# define _EVENTMODULE_H_

#include <queue>

#include "AEventModule.hpp"
#include "RenderModule.hpp"
#include "StateModule.hpp"
#include "Event.hpp"

class EventModule : public Engine::AEventModule
{
private:
	StateModule*	_stateModule;
	RenderModule*	_renderModule;
public:
	EventModule();
	~EventModule();

	void	initialize();
	void	update();
	void	unload();
};

#endif /* _EVENTMANAGER_H_ */
