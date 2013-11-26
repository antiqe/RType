#include <exception>

#include "WThread.hpp"

namespace Ultra
{
	WThread::WThread()
	  : _id(0), _handle(0)
	{

	}

	WThread::~WThread()
	{
		if (this->_handle)
			CloseHandle(this->_handle);
	}

	void WThread::create(void* (*routine)(void*), void *param)
	{
		if (!(this->_handle = CreateThread(0, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(routine), param, 0, &this->_id)))
			throw std::exception(); // TODO: revoir ici (GetLastError())
	}

	void WThread::exit()
	{
		if (this->_handle)
		{
			if (TerminateThread(this->_handle, 1) == 0)
				throw std::exception(); // TODO: revoir ici (GetLastError())
			CloseHandle(this->_handle);
			this->_handle = 0;
		}
	}

	void WThread::wait()
	{
		if (this->_handle)
		{
			if (WaitForSingleObject(this->_handle, INFINITE) == WAIT_FAILED)
				throw std::exception(); // TODO: revoir ici (GetLastError())
			CloseHandle(this->_handle);
			this->_handle = 0;
		}
	}

	WThread*	WThread::clone() const
	{
		return (new WThread);
	}
}
