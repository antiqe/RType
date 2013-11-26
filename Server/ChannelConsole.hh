//
// ChannelConsole.hh
// 
// Made by Guiho Ronan
// 
// Started on  Wed May  8 17:54:02 2013 Guiho Ronan
// Last update Sat May 11 20:37:13 2013 Guiho Ronan
//

#ifndef __CHANNELCONSOLE_HH__
#define __CHANNELCONSOLE_HH__

#include "LogMessage.hpp"
#include "IChannel.hh"

#include <string>

namespace Logging
{
  class ChannelConsole : public IChannel
  {
  private:
    std::string _name;
  public:
    static const std::string refPriorityWin[];
	static const int refPriorityUnix[];
  public:
    ChannelConsole();
    virtual const std::string &getName() const;
    virtual bool isValid() const;
    virtual void setName(const std::string &name) const;
    virtual void write(const Message &msg) const;
  };
}

#endif
