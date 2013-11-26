#include <unistd.h>
#include <sys/time.h>

#include "LFramer.hpp"

namespace Ultra
{
	LFramer::LFramer(size_t frame)
		: AFramer(frame)
	{

	}

	LFramer::~LFramer()
	{

	}

	bool	LFramer::wait() const
	{
		usleep(this->latence() * 1000000.0f);
		return (true);
	}

	double	LFramer::time() const
	{
		struct timeval time;

		gettimeofday(&time, NULL);
		return (static_cast<double>(time.tv_sec) + (static_cast<double>(time.tv_usec) / 1000000.0f));
	}
}