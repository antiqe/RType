#include <sys/time.h>
#include <unistd.h>

#include "LTimer.hpp"

namespace Ultra
{
  LTimer::LTimer()
    : ATimer<1000000>()
  {

  }
  
  LTimer::~LTimer()
  {
    
  }
  
  
  Time<1000000>	LTimer::clock() const
  {
    struct timeval time;
    
    gettimeofday(&time, NULL);
    return (Time<1000000>(time.tv_sec, time.tv_usec));
  }
}
