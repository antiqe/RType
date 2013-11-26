#ifndef __I_MUTEX_H__
# define __I_MUTEX_H__

namespace Ultra
{
	class IMutex
	{
	public:
		virtual ~IMutex() {}

		virtual bool trylock() = 0;
		virtual void lock() = 0;
		virtual void unlock() = 0;
	};
}

#endif