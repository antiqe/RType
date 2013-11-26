#ifndef _PLAYER_H_
# define _PLAYER_H_

#include "GameObject.hpp"

namespace Engine
{
	class Player : public Engine::GameObject
	{
	public:
		Player();
		~Player();
	};
}

#endif