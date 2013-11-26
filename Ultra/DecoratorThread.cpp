#include "DecoratorThread.hpp"
#include "WTimer.hpp"
#include "LTimer.hpp"
#ifdef _WIN32
#include "WThread.hpp"
#else
#include "LThread.hpp"
#endif

#include <iostream>

namespace Ultra
{
	DecoratorThread::DecoratorThread()
	{
#ifdef _WIN32
		this->_timer = new WTimer();
		this->_thread = new WThread();
#else
		this->_timer = new LTimer();
		this->_thread = new LThread();
#endif
	}

	DecoratorThread::~DecoratorThread()
	{
		if (this->isRunning())
			this->_thread->exit();
		delete this->_thread;
		delete this->_timer;
	}

	bool	DecoratorThread::isRunning() const
	{
		return (this->_timer->isRunning());
	}

	double	DecoratorThread::runTime() const
	{
		return (this->_timer->getTime());
	}

	void	DecoratorThread::create(void* (*routine)(void*), void* param)
	{
		this->_timer->start();
		this->_thread->create(routine, param);
	}

	void	DecoratorThread::wait()
	{
		this->_timer->stop();
		this->_timer->reset();
		this->_thread->wait();
	}

	void	DecoratorThread::exit()
	{
		this->_timer->stop();
		this->_timer->reset();
		this->_thread->exit();
	}

	DecoratorThread*	DecoratorThread::clone() const
	{
		return (new DecoratorThread);
	}
}