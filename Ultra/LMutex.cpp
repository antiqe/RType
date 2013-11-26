#include "LMutex.hpp"

namespace Ultra
{
  LMutex::LMutex()
    : _islock(false)
  {
    pthread_mutexattr_t attr;

    pthread_mutexattr_init(&attr);
    pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
    pthread_mutex_init(&(this->_mutex), &attr);
  }

  LMutex::~LMutex()
  {
    if (!this->_islock)
      pthread_mutex_unlock(&(this->_mutex));
  }

  bool LMutex::trylock()
  {
    if (this->_islock)
      return false;
    this->lock();
    return true;
  }

  void LMutex::lock()
  {
    pthread_mutex_lock(&(this->_mutex));
    this->_islock = true;
  }
  
  void LMutex::unlock()
  {
    pthread_mutex_unlock(&(this->_mutex));
    this->_islock = false;
  }
}
