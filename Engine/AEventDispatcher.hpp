#ifndef __AEVENT_DISPATCHER_H__
# define __AEVENT_DISPATCHER_H__

#include <list>
#include <string>
#include <sys/types.h>

#include "Event.hpp"
#include "EventListener.hpp"
#include "Callback.hpp"

namespace Engine
{
	class AEventDispatcher
	{
	protected:
		std::list<EventListener>	_els;
	public:
		AEventDispatcher();
	  virtual ~AEventDispatcher();

		virtual void	addEventListener(std::string const& name, std::string const& type, Callback::EventFunction callback, int priority = 0);
		virtual void	addEventListener(std::string const& name, Callback::EventFunction callback, int priority = 0);
		virtual void	removeEventListener(std::string const& name, std::string const& type);
		virtual void	removeEventListener(std::string const& name);
		virtual void	removeAllEventListener(std::string const& name, std::string const& type);
		virtual void	removeAllEventListener(std::string const& name);
		virtual bool	hasEventListener(std::string const& name, std::string const& type) const;
		virtual bool	hasEventListener(std::string const& name) const;
		virtual void	dispatchEvent(Event* event) const = 0;
	};
}

#endif /* _AEVENT_DISPATCHER_H_ */
