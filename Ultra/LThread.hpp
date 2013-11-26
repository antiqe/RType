#pragma once

#include <pthread.h>

#include "IThread.hpp"

namespace Ultra
{
  class LThread : public IThread
  {
  private:
    typedef void* (*Handle)(void *);
    unsigned long _id;
    Handle _handle;
  public:
    LThread();
    ~LThread();

    virtual void create(Handle routine, void *param);
    virtual void exit();
    virtual void wait();

    virtual LThread *clone() const;
  };
}
