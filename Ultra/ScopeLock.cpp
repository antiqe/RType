#include "ScopeLock.hpp"

namespace Ultra
{
	ScopeLock::ScopeLock(IMutex *mutex)
		: _mutex(mutex)
	{
		if (this->_mutex)
			this->_mutex->lock();
	}

	ScopeLock::~ScopeLock()
	{
		if (this->_mutex)
			this->_mutex->unlock();
	}
}