#include "NetworkEvent.hpp"

namespace Engine
{
	NetworkEvent::NetworkEvent(std::string const &type, Message *msg)
		: Event(Event::NETWORK, type)
	{
		std::map<std::string, Ultra::Value> attrs = msg->getAllAttrs();
		std::map<std::string, Ultra::Value>::iterator it = attrs.begin();

		for (; it != attrs.end(); ++it)
			this->_attr[it->first] = it->second;
	}

	NetworkEvent::~NetworkEvent()
	{

	}
}