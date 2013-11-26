//
// Logger.hpp
// 
// Made by Guiho Ronan
// 
// Started on  Wed May  8 17:13:25 2013 Guiho Ronan
// Last update Mon May 13 10:53:02 2013 ronan guiho
//

#ifndef __LOGGER_HPP__
#define __LOGGER_HPP__

#include <list>
#include <string>
#include <algorithm>

#include "LogMessage.hpp"
#include "IChannel.hh"

namespace Logging
{
  class Logger
  {
  private:
    std::string _name;
    std::list<IChannel *> _channels;
    Logging::Message::MessagePriority _priority;
    struct match_channel
    {
      std::string _name;
      match_channel(const std::string &name) : _name(name) {}
      bool operator()(IChannel *channel)
      { return (this->_name == channel->getName()); }
    };
  public:
    Logger(const std::string &name)
      : _name(name), _priority(Logging::Message::TRACE)
    {
    }
    void addChannel(IChannel *channel)
    {
      this->_channels.push_back(channel);
    }
    bool deleteChannel(const std::string &name)
    {
      std::list<IChannel *>::iterator it;

      it = std::remove_if(this->_channels.begin(), this->_channels.end(),
			  match_channel(name));
      if (it != this->_channels.end())
	{
	  this->_channels.erase(it);
	  return (true);
	}
      return (false);
    }
    template <typename T>
    IChannel *getChannel()
    {
      std::list<IChannel *>::iterator it;

      for (it = this->_channels.begin(); it != this->_channels.end(); ++it)
	if (dynamic_cast<T *>(*it))
	  return (*it);
      return (0);
    }
    IChannel *getChannel(const std::string &name)
    {
      std::list<IChannel *>::iterator it;

      for (it = this->_channels.begin(); it != this->_channels.end(); ++it)
	if ((*it)->getName() == name)
	  return (*it);
      return (0);
    }
    void log(const Message &msg)
    {
      this->writeAllChannel(msg);
    }
    void log(const std::string &text, const Message::MessagePriority prio)
    {
      Message msg(text, "None", prio);

      this->writeAllChannel(msg);
    }
    const std::string &getName() const
    {
      return (this->_name);
    }
    const Logging::Logger &operator<<(const Message &msg)
    {
      this->writeAllChannel(msg);
      return (*this);
    }
    const Logging::Logger &operator<<(const std::string &text)
    {
      Message msg(text, "", this->_priority);

      this->writeAllChannel(msg);
      return (*this);
    }
    const Logging::Logger &operator<<(const Logging::Message::MessagePriority prio)
    {
      this->_priority = prio;
      return (*this);
    }
  private:
    void writeAllChannel(const Message &msg)
    {
      for (std::list<IChannel *>::iterator it = this->_channels.begin();
	   it != this->_channels.end(); ++it)
	(*it)->write(msg);
    }
  };
}

#endif
