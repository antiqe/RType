#ifndef _STATE_AUTH_H_
# define _STATE_AUTH_H_

namespace Network
{
  enum StateService
    {
      BUSY = 1,
      MAINTENANCE = 2,
      FREE = 2,
      OVERLOAD = 3
    };

    enum StateAccount
    {
      ACCEPT = 1,
      REFUSED = 2,
      BAN = 3
    };
}

#endif