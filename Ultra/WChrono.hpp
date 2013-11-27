#ifndef _WCHRONO_H_
# define _WCHRONO_H_

#include "AChrono.hpp"

namespace Ultra
{
	class WChrono : public AChrono<1000>
	{
	public:
		WChrono();
		~WChrono();

		Time<1000>	clock() const;
		WChrono*	clone() const;
	};
}

#endif