//
// Account.cpp
// 
// Made by Guiho Ronan
// 
// Started on  Sat Oct 26 20:34:07 2013 Guiho Ronan
// Last update Sat Oct 26 20:34:53 2013 Guiho Ronan
//

#include "Account.hh"
#include "ScopeLock.hpp"

#ifdef _WIN32
#include "WMutex.hpp"
#else
#include "LMutex.hpp"
#endif

Account::Account(std::string const &login, std::string const &passwd)
  : _login(login), _passwd(passwd), _state(Account::OFFLINE)
{
#ifdef _WIN32
  _mutex = new Ultra::WMutex();
#else
  _mutex = new Ultra::LMutex();
#endif
}

std::string Account::getPassword() const
{
  Ultra::ScopeLock sl(this->_mutex);

  return (this->_passwd);
}

Account::State Account::getState() const
{
  Ultra::ScopeLock sl(this->_mutex);

  return (this->_state);
}

void Account::setState(Account::State const state)
{
  Ultra::ScopeLock sl(this->_mutex);

  this->_state = state;
}

void Account::setRoom(Room *room)
{
  Ultra::ScopeLock sl(this->_mutex);

  this->_room = room;
}

std::string Account::getLogin() const
{
  return (this->_login);
}

Room *Account::getRoom() const
{
  Ultra::ScopeLock sl(this->_mutex);

  return (this->_room);
}
