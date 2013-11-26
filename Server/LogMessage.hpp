/*
** Message.hh
** 
** Made by Guiho Ronan
** 
** Started on  Wed May  8 16:17:14 2013 Guiho Ronan
// Last update Sun May 12 16:35:02 2013 Guiho Ronan
*/

#ifndef __LOGGMESSAGE_HH__
#define __LOGGMESSAGE_HH__

#include <map>
#include <ctime>
#include <string>

namespace Logging
{
  class Message
  {
  public:
    typedef enum MessagePriority
      {
	CRITICAL = 0,
	DEBUG,
	FATAL,
	_ERROR,
	INFORMATION,
	NOTICE,
	TRACE,
	WARNING
      } MessagePriority;
    static const std::string refPriority[];
  private:
    std::string _text;
    std::string _source;
    std::string _process;
    time_t _time;
    MessagePriority _priority;
  public:
    Message(const std::string &text, const std::string &source,
	    const MessagePriority prio = NOTICE);
    Message(const Message &msg);
    MessagePriority getPriority() const;
    const std::string &getText() const;
    const std::string &getSource() const;
    const std::string &getProcess() const;
    void setText(const std::string &text);
    void setSource(const std::string &source);
    void setProcess(const std::string &process);
    void setPriority(const MessagePriority prio);
    std::string serialize() const;
  };
}

#endif
