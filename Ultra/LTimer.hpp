#ifndef _LTIMER_H_
# define _LTIMER_H_

#include "ATimer.hpp"
#include "Time.hpp"

namespace Ultra
{
  class LTimer : public ATimer<1000000>
  {
  public:
    LTimer();
    virtual ~LTimer();
    
    virtual Time<1000000>	clock() const;
  };
}

#endif /* _LTIMER_H_ */
