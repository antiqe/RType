#ifndef _TIME_H_
# define _TIME_H_

namespace Ultra
{
  template <int P>
  struct Time
  {
    int	sec;
    int	usec;
    
    Time(int sec = 0, int usec = 0)
    {
      this->sec = sec;
      this->usec = usec;
    }
    virtual ~Time() {}
  };
  
  template <int P>
  Time<P>	operator-(Time<P> const& t1, Time<P> const& t2)
  {
    Time<P>	t((t1.sec - t2.sec) * (t1.sec < t2.sec ? -1 : 1), t1.usec - t2.usec);
    
    if (t.usec < 0)
      {
	--t.sec;
	t.usec += P;
      }
    return (t);
  }
}

#endif /* _TIME_H_ */
