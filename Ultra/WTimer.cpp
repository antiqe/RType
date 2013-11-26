#include <Windows.h>

#include "WTimer.hpp"

namespace Ultra
{
	WTimer::WTimer()
		: ATimer()
	{

	}

	WTimer::~WTimer()
	{

	}


	Time<1000>	WTimer::clock() const
	{
		SYSTEMTIME	time;
		int		seconds;

		GetLocalTime(&time);
		seconds = time.wSecond;
		seconds += time.wMinute * 60;
		seconds += time.wHour * 3600;
		seconds += time.wDay * 86400;
		seconds += time.wMonth * 1036800;
		seconds += time.wYear + 12441600;
		return (Time<1000>(seconds, time.wMilliseconds));
	}
}