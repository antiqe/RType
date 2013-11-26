#include <cstdio>
#include <iostream>

#include "RoomInfo.hpp"

RoomInfo::RoomInfo(unsigned short const id, const std::string &name, bool isPrivate, int playerIn, int playerMax)
  : _id(id), _name(name), _isPrivate(isPrivate), _playerIn(playerIn), _playerMax(playerMax)
{
}

RoomInfo::~RoomInfo()
{
}

std::string RoomInfo::toString()
{
  size_t	size = 1000;
  char		str[1000];
#ifdef _WIN32
  _snprintf(str, size, "  %-10s%-60s%-20d%-20d", ((this->_isPrivate) ? "Yes" : "No"), this->_name.c_str(), this->_playerIn, this->_playerMax);
#else
  snprintf(str, size, "  %-10s%-60s%-20d%-20d", ((this->_isPrivate) ? "Yes" : "No"), this->_name.c_str(), this->_playerIn, this->_playerMax);
#endif
  return str;
}

std::string	RoomInfo::getName() const
{
  return this->_name;
}

void		RoomInfo::setName(const std::string &name)
{
  this->_name = name;
}

bool		RoomInfo::isPrivate() const
{
  return this->_isPrivate;
}

void		RoomInfo::setIsPrivate(bool isPrivate)
{
  this->_isPrivate = isPrivate;
}

int		RoomInfo::getPlayerIn() const
{
  return this->_playerIn;
}

void		RoomInfo::setPlayerIn(int playerIn)
{
  this->_playerIn = playerIn;
}

int		RoomInfo::getPlayerMax() const
{
  return this->_playerMax;
}

void		RoomInfo::setPlayerMax(int playerMax)
{
  this->_playerMax = playerMax;
}

unsigned short		RoomInfo::getID() const
{
	return (this->_id);
}

void	RoomInfo::setID(unsigned short const id)
{
	this->_id = id;
}