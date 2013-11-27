#include "StateModule.hpp"
#include "Exception.hpp"
#include "State.hpp"
#include "ConnectionState.hpp"
#include "GameState.hpp"
#include "PlayState.hpp"
#include "PlayCreateState.hpp"
#include "PlayJoinState.hpp"
#include "RoomState.hpp"
#include "SettingsState.hpp"

StateModule::StateModule()
	: Engine::AStateModule(State::CONNECTION)
{

}

StateModule::~StateModule()
{

}

void	StateModule::initialize()
{
	this->_statePool[State::CONNECTION] = new ConnectionState;
	this->_statePool[State::GAME] = new GameState;
	this->_statePool[State::PLAY] = new PlayState;
	this->_statePool[State::PLAY_CREATE] = new PlayCreateState;
	this->_statePool[State::PLAY_JOIN] = new PlayJoinState;
	this->_statePool[State::ROOM] = new RoomState;
	this->_statePool[State::SETTINGS] = new SettingsState;
	for (std::map<std::string, Engine::AState*>::iterator it = this->_statePool.begin(); it != this->_statePool.end(); ++it)
		it->second->initialize();
	this->_stateStack.push(this->_statePool[this->_mainName]);
}

void	StateModule::update()
{
	if (!this->_stateStack.empty())
		this->_stateStack.top()->update();
}

void	StateModule::unload()
{
	for (std::map<std::string, Engine::AState*>::iterator it = this->_statePool.begin(); it != this->_statePool.end(); ++it)
	{
		it->second->unload();
		delete it->second;
	}
}