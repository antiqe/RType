#ifndef __ITHREAD_H__
# define __ITHREAD_H__

# include "IPrototype.hpp"

namespace Ultra
{
	class IThread : public Ultra::IPrototype<IThread>
	{
	public:
	  virtual ~IThread() {}
	  
	  virtual void create(void* (*routine)(void*), void *param) = 0;
	  virtual void exit() = 0;
	  virtual void wait() = 0;
	};
}

#endif
