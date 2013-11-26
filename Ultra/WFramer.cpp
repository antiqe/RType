#include <Windows.h>

#include "WFramer.hpp"

namespace Ultra
{
	WFramer::WFramer(size_t frame)
		: AFramer(frame)
	{

	}

	WFramer::~WFramer()
	{

	}

	bool	WFramer::wait() const
	{
		Sleep(static_cast<DWORD>(this->latence() * 1000.0f));
		return (true);
	}

	double	WFramer::time() const
	{
		SYSTEMTIME	time;
		double		seconds;

		GetLocalTime(&time);
		seconds = time.wMilliseconds / 1000.0f;
		seconds += time.wSecond;
		seconds += time.wMinute * 60.0f;
		seconds += time.wHour * 3600.0f;
		seconds += time.wDay * 86400.0f;
		seconds += time.wMonth * 1036800.0f;
		seconds += time.wYear + 12441600.0f;
		return (seconds);
	}
}