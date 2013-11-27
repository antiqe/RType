#ifndef _LCHRONO_H_
# define _LCHRONO_H_

#include "AChrono.hpp"

namespace Ultra
{
	class LChrono : public AChrono<1000000>
	{
	public:
		LChrono();
		~LChrono();

		Time<1000000>	clock() const;
		LChrono*		clone() const;
	};
}

#endif