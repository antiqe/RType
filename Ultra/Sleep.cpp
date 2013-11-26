#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif


#include "Sleep.hpp"

namespace Ultra
{
  void Sleep::usleep(unsigned int const usec)
  {
#ifdef _WIN32
    HANDLE timer; 
    LARGE_INTEGER ft; 

    ft.QuadPart = -(long int)(10*usec);
    timer = CreateWaitableTimer(0, true, 0); 
    SetWaitableTimer(timer, &ft, 0, 0, 0, 0); 
    WaitForSingleObject(timer, INFINITE); 
    CloseHandle(timer); 
#else
    ::usleep(usec);
#endif
  }
}
