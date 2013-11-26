#include <Windows.h>

#include "WChrono.hpp"

namespace Ultra
{
	WChrono::WChrono()
	{

	}

	WChrono::~WChrono()
	{

	}

	Ultra::Time<1000>	WChrono::clock() const
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

	WChrono*			WChrono::clone() const
	{
		return (new WChrono());
	}
}