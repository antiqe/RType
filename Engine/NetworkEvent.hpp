#ifndef __NETWORK_EVENT_HPP__
#define __NETWORK_EVENT_HPP__

#include "Message.hpp"
#include "Event.hpp"

namespace Engine
{
	class NetworkEvent : public Event
	{
	public:
		NetworkEvent(std::string const &type, Message *msg);
		virtual ~NetworkEvent();
	};
}

#endif