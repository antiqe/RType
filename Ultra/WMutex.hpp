#ifndef __W_MUTEX_H__
# define __W_MUTEX_H__

#include <Windows.h>

#include "IMutex.hpp"

namespace Ultra
{
	class WMutex : public IMutex
	{
	private:
		CRITICAL_SECTION _cs;

	public:
		WMutex();
		~WMutex();

		bool trylock();
		void lock();
		void unlock();
	};
}

#endif