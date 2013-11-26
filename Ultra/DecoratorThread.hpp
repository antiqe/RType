#ifndef _DECORATORTHREAD_H_
# define _DECORATORTHREAD_H_

#include "IThread.hpp"
#include "ITimer.hpp"
#include "IPrototype.hpp"

namespace Ultra
{
	class DecoratorThread : public IThread
	{
	private:
		IThread*	_thread;
		ITimer*		_timer;
	public:
		DecoratorThread();
		~DecoratorThread();

		bool	isRunning() const;
		double	runTime() const;

		void create(void* (*routine)(void*), void *param);
		void exit();
		void wait();

		DecoratorThread*	clone() const;
	};
}

#endif