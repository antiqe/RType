#ifndef _STATE_PLAYER_H_
# define _STATE_PLAYER_H_

namespace Network
{
	enum StatePlayer
    {
      NONE	= 1,
      READY	= 2,
      LEFT	= 3
    };

	enum StateSpecPlayer
	{
		MASTER = 1,
		SIMPLE = 2
	};
}

#endif