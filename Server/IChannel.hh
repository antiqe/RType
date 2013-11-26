//
// IChannel.hh
// 
// Made by Guiho Ronan
// 
// Started on  Wed May  8 17:14:38 2013 Guiho Ronan
// Last update Sat May 11 20:36:58 2013 Guiho Ronan
//

#ifndef __ICHANNEL_HH__
#define __ICHANNEL_HH__

#include <string>

#include "LogMessage.hpp"

namespace Logging
{
  class IChannel
  {
  public:
    virtual const std::string &getName() const = 0;
    virtual bool isValid() const = 0;
    virtual void setName(const std::string &name) const = 0;
    virtual void write(const Message &msg) const = 0;
  };
}

#endif
