#ifndef __ANETWORKMODULE_H__
#define __ANETWORKMODULE_H__

#include <queue>
#include <functional>

#include "AModule.hpp"
#include "ISocket.hpp"
#include "APacket.hpp"
#include "Event.hpp"

namespace Engine
{
	class ANetworkModule : public AModule
	{
	protected:
		unsigned short										_port;
		std::string											_host;
		bool												_started;
		std::queue<std::pair<APacket*, ISocket::Protocol> >	_sendQueue;
	public:
		ANetworkModule();
		virtual ~ANetworkModule();

		std::string const& getID() const;

		void	setPort(unsigned short const port);
		void	setHost(std::string const &host);

		unsigned short			getPort() const;
		std::string const&		getHost() const;

		bool			isStarted() const;

		virtual bool	start() = 0;
		virtual void	stop() = 0;

		void	addMessage(APacket *pck, ISocket::Protocol proto);
	};
}

#endif