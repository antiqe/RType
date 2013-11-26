#include "LThread.hpp"

namespace Ultra
{
  LThread::LThread()
    : _id(0), _handle(0)
  {


  }

  LThread::~LThread()
  {

  }

  void LThread::create(Handle routine, void *param)
  {
    if (routine)
      pthread_create(&(this->_id), 0, routine, param);
  }

  void LThread::exit()
  {
    if (this->_id)
      pthread_cancel(this->_id);
  }

  void LThread::wait()
  {
    if (this->_id)
      pthread_join(this->_id, 0);
  }

  LThread *LThread::clone() const
  {
    return (new LThread);
  }

};
