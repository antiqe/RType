#ifndef _GAMEOBJECTFACTORY_H_
# define _GAMEOBJECTFACTORY_H_

#include "GameObject.hpp"
#include "Factory.hpp"

class GameObjectFactory : public Ultra::Factory<Engine::GameObject>
{
public:
	GameObjectFactory();
	~GameObjectFactory();
};

#endif