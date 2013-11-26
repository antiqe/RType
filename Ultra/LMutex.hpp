#pragma once

#include "IMutex.hpp"

#include <pthread.h>

namespace Ultra
{
  class LMutex : public IMutex
  {
  private:
    pthread_mutex_t _mutex;
    bool _islock;
  public:
    LMutex();
    ~LMutex();

    bool trylock();
    void lock();
    void unlock();
  };
}
