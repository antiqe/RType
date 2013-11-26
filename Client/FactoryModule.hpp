#ifndef _FACTORYMODULE_H_
# define _FACTORYMODULE_H_

#include "AFactoryModule.hpp"
#include "MessageFactory.hpp"
#include "GameObjectFactory.hpp"

class FactoryModule : public Engine::AFactoryModule
{
private:
	GameObjectFactory*			_gameObjets;
	MessageFactory*				_messages;
public:
	FactoryModule();
	~FactoryModule();

	void	initialize();
	void	update();
	void	unload();

	Message*			createMessage(unsigned short id);
	Engine::GameObject*	createGameObject(std::string const& id);
};

#endif