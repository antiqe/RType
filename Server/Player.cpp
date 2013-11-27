#include "Player.hh"
#include "Account.hh"
#include "ScopeLock.hpp"

#ifdef _WIN32
#include "WMutex.hpp"
#include "WTimer.hpp"
#else
#include "LMutex.hpp"
#include "LTimer.hpp"
#endif

Player::Player(char const rank, int const id, Account *acc, Player::StateSpecPlayer const state)
	: _rank(rank), _id(id), _acc(acc), _ship(0), _latency(0), _stateSpec(state), _state(Player::NONE)
{
#ifdef _WIN32
  _mutex = new Ultra::WMutex();
  _lping = new Ultra::WTimer();
#else
  _mutex = new Ultra::LMutex();
  _lping = new Ultra::LTimer();
#endif
}

Account *Player::getAccount() const
{
  Ultra::ScopeLock sl(this->_mutex);
    
  return (this->_acc);
}

void Player::setAccount(Account *acc)
{
  Ultra::ScopeLock sl(this->_mutex);
    
  this->_acc = acc;
}

char Player::getState() const
{
  Ultra::ScopeLock sl(this->_mutex);

  return (this->_state);
}

void Player::setState(Player::StatePlayer const state)
{
  Ultra::ScopeLock sl(this->_mutex);

  this->_state = state;
}

char Player::getStateSpec() const
{
  Ultra::ScopeLock sl(this->_mutex);

  return (this->_stateSpec);
}

void Player::setStateSpec(Player::StateSpecPlayer const state)
{
  Ultra::ScopeLock sl(this->_mutex);

  this->_stateSpec = state;
}

void Player::setShip(char const ship)
{
  Ultra::ScopeLock sl(this->_mutex);

  this->_ship = ship;
}

char Player::getShip() const
{
  Ultra::ScopeLock sl(this->_mutex);
  
  return (this->_ship);
}

int Player::getID() const
{
  Ultra::ScopeLock sl(this->_mutex);

  return (this->_id);
}

void Player::setID(int const id)
{
  Ultra::ScopeLock sl(this->_mutex);

  this->_id = id;
}

struct sockaddr_in const &Player::getUInfo() const
{
  Ultra::ScopeLock sl(this->_mutex);

  return (this->_uinfo);
}

void Player::setUInfo(struct sockaddr_in const &uinfo)
{
  Ultra::ScopeLock sl(this->_mutex);

  this->_uinfo = uinfo;
}

long Player::getLatency() const
{
  Ultra::ScopeLock sl(this->_mutex);

  return (this->_latency);
}

void Player::startTimer()
{
  Ultra::ScopeLock sl(this->_mutex);

  this->_lping->start();
}

void Player::stopTimer()
{
  Ultra::ScopeLock sl(this->_mutex);
  
  this->_lping->stop();
  this->_latency = this->_lping->getTime();
}

void Player::setRank(char const rank)
{
  Ultra::ScopeLock sl(this->_mutex);
  this->_rank = rank;
}

char Player::getRank() const
{
	return (this->_rank);
}