#ifndef __WTHREAD_H__
# define __WTHREAD_H__

#include <Windows.h>

#include "IThread.hpp"

namespace Ultra
{
	class WThread : public IThread
	{
	private:
		DWORD _id;
		HANDLE _handle;
	public:
		WThread();
		~WThread();

		void create(void* (*routine)(void*), void *param);
		void exit();
		void wait();

		WThread*	clone() const;
	};
}

#endif
