#include "WMutex.hpp"

namespace Ultra
{
	WMutex::WMutex()
	{
		InitializeCriticalSection(&this->_cs);
	}

	WMutex::~WMutex()
	{
		DeleteCriticalSection(&this->_cs);
	}

	bool WMutex::trylock()
	{
		return (TryEnterCriticalSection(&this->_cs) != 0);
	}

	void WMutex::lock()
	{
		EnterCriticalSection(&this->_cs);
	}

	void WMutex::unlock()
	{
		LeaveCriticalSection(&this->_cs);
	}
}