#include <sys/time.h>
#include <unistd.h>

#include "LChrono.hpp"

namespace Ultra
{
	LChrono::LChrono()
	{

	}

	LChrono::~LChrono()
	{

	}

	Ultra::Time<1000000>	LChrono::clock() const
	{
		struct timeval time;

		gettimeofday(&time, NULL);
		return (Time<1000000>(time.tv_sec, time.tv_usec));
	}

	LChrono*				LChrono::clone() const
	{
		return (new LChrono());
	}
}