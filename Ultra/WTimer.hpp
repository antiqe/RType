#ifndef _WTIMER_H_
# define _WTIMER_H_

#include "ATimer.hpp"
#include "Time.hpp"

namespace Ultra
{
	class WTimer : public ATimer<1000>
	{
	public:
		WTimer();
		virtual ~WTimer();

		virtual Time<1000>	clock() const;
	};
}

#endif /* _WTIMER_H_ */
