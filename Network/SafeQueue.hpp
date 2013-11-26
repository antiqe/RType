#ifndef __SAFEQUEUE_HPP__
#define __SAFEQUEUE_HPP__

#include <queue>

#include "IMutex.hpp"
#include "ScopeLock.hpp"

#ifdef _WIN32
#include "WMutex.hpp"
#else
#include "LMutex.hpp"
#endif

template<typename T>
class SafeQueue
{
private:
  Ultra::IMutex *_mutex;
  std::queue<T> q;
public:
  SafeQueue()
  {
    #ifdef _WIN32
    _mutex = new Ultra::WMutex();
    #else
    _mutex = new Ultra::LMutex();
    #endif
  }

  ~SafeQueue()
  {
    delete _mutex;
  }

  void push(T data)
  {
    Ultra::ScopeLock slock(this->_mutex);

    q.push(data);
  }

  bool isEmpty() const
  {
    Ultra::ScopeLock slock(this->_mutex);
    return q.empty();
  }

  T pop()
  {
    Ultra::ScopeLock slock(this->_mutex);
    T tmp;

    tmp = q.front();
    q.pop();
    return tmp;
  }
};

#endif