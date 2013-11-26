#include "FactoryModule.hpp"
#include "Player.hh"

FactoryModule::FactoryModule()
{

}

FactoryModule::~FactoryModule()
{

}

void	FactoryModule::initialize()
{
	this->_messages = new MessageFactory();
	this->_gameObjets = new GameObjectFactory();
}

void	FactoryModule::update()
{

}

void	FactoryModule::unload()
{
	delete this->_messages;
	delete this->_gameObjets;
}

Message*			FactoryModule::createMessage(unsigned short id)
{
	return (this->_messages->create(id));
}

Engine::GameObject*	FactoryModule::createGameObject(std::string const& id)
{
	return (this->_gameObjets->create(id));
}
