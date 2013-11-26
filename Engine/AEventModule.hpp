#ifndef _AEVENTMODULE_H_
# define _AEVENTMODULE_H_

# include <string>
# include <queue>

# include "AModule.hpp"
# include "Event.hpp"

namespace Engine
{
	class AEventModule : public AModule
	{
	protected:
		std::queue<Event*>	_eventQueue;
	public:
		AEventModule();
		virtual ~AEventModule();

		std::string const&	getID() const;
	};
};

#endif