//
// ChannelConsole.cpp
//
// Made by Guiho Ronan
//
// Started on  Wed May  8 17:57:41 2013 Guiho Ronan
//

#include <iostream>

#ifdef _WIN32
#include <windows.h>
#endif

#include "ChannelConsole.hh"

const std::string Logging::ChannelConsole::refPriorityWin[] =
{
  "\033[0;31m",
  "\033[0;35m",
  "\033[0;31m",
  "\033[0;31m",
  "\033[0;33m",
  "\033[0;32m",
  "\033[0;37m",
  "\033[0;33m"
};

const int Logging::ChannelConsole::refPriorityUnix[] =
{
	12,
	13,
	12,
	12,
	14,
	10,
	15,
	14
};

Logging::ChannelConsole::ChannelConsole()
  : _name("Console")
{
}

const std::string &Logging::ChannelConsole::getName() const
{
  return (this->_name);
}

bool Logging::ChannelConsole::isValid() const
{
  return (true);
}

void Logging::ChannelConsole::setName(const std::string &) const
{
}

void Logging::ChannelConsole::write(const Message &msg) const
{
#ifdef _WIN32

  HANDLE cHandle;

  cHandle = GetStdHandle(STD_OUTPUT_HANDLE);
  SetConsoleTextAttribute(cHandle, Logging::ChannelConsole::refPriorityUnix[msg.getPriority()]);
  
  std::cout << msg.serialize();

#else

  std::cout << Logging::ChannelConsole::refPriorityWin[msg.getPriority()] <<
    msg.serialize() << "\033[0;40m";

#endif
}
