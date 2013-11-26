#ifndef __SCOPE_LOCK_H__
# define __SCOPE_LOCK_H__

# include "IMutex.hpp"

namespace Ultra
{
	class ScopeLock
	{
	private:
		IMutex *_mutex;

	public:
		ScopeLock(IMutex *);
		~ScopeLock();
	};
}

#endif