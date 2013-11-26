#ifndef __MESSAGEFACTORY_HH__
#define __MESSAGEFACTORY_HH__

#include "Factory.hpp"

class Message;

class MessageFactory : public Ultra::Factory<Message, unsigned short>
{
public:
	MessageFactory();
	~MessageFactory();

	Message *createMessage(unsigned short const id) const;
};

#include "Message.hpp"

#endif