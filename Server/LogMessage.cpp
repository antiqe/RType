//
// Message.cpp
// 
// Made by Guiho Ronan
// 
// Started on  Wed May  8 16:45:11 2013 Guiho Ronan
// Last update Sat Jun  1 11:07:15 2013 ronan guiho
//

#include <map>
#include <string>
#include <sstream>

#include "LogMessage.hpp"

const std::string Logging::Message::refPriority[] =
{
  "Critical",
  "Debug",
  "Fatal",
  "Error",
  "Info",
  "Notice",
  "Trace",
  "Warning"
};

Logging::Message::Message(const std::string &text, const std::string &source,
		 const Logging::Message::MessagePriority prio)
  : _text(text), _source(source), _process(""), _time(time(0)), _priority(prio)
{
}

Logging::Message::Message(const Message &msg)
  : _text(msg.getText()), _source(msg.getSource()), \
    _process(msg.getProcess()),_time(time(0)), _priority(msg.getPriority())
{
}

const std::string &Logging::Message::getText() const
{
  return (this->_text);
}

const std::string &Logging::Message::getSource() const
{
  return (this->_source);
}

const std::string &Logging::Message::getProcess() const
{
  return (this->_process);
}

Logging::Message::MessagePriority Logging::Message::getPriority() const
{
  return (this->_priority);
}

void Logging::Message::setText(const std::string &text)
{
  this->_text = text;
}

void Logging::Message::setSource(const std::string &source)
{
  this->_source = source;
}

void Logging::Message::setProcess(const std::string &process)
{
  this->_process = process;
}

void Logging::Message::setPriority(const Logging::Message::MessagePriority prio)
{
  this->_priority = prio;
}

std::string Logging::Message::serialize() const
{
  std::stringstream ss;
  std::tm *ltm = localtime(&this->_time);

  ss << "[" << ltm->tm_mday << "/" << (1 + ltm->tm_mon) << "/"
     << (1900 + ltm->tm_year) << " " << ltm->tm_hour << ":" <<
    (1 + ltm->tm_min) << ":" << (1 + ltm->tm_sec) << "] ";
  ss << "[" << this->refPriority[this->_priority]  << "] ";
  ss << "[" << this->_source << "] ";
  ss << this->_text << std::endl;
  return (ss.str());
}
