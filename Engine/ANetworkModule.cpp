#include "ANetworkModule.hpp"

namespace Engine
{
	ANetworkModule::ANetworkModule()
		: AModule(180), _port(0), _host(""), _started(false)
	{

	}

	ANetworkModule::~ANetworkModule()
	{

	}

	std::string const& ANetworkModule::getID() const
	{
		return (AModule::NETWORK);
	}

	void	ANetworkModule::setPort(unsigned short const port)
	{
		this->_port = port;
	}

	void	ANetworkModule::setHost(std::string const &host)
	{
		this->_host = host;
	}

	unsigned short			ANetworkModule::getPort() const
	{
		return (this->_port);
	}

	std::string const&		ANetworkModule::getHost() const
	{
		return (this->_host);
	}

	bool	ANetworkModule::isStarted() const
	{
		return (this->_started);
	}

	void	ANetworkModule::addMessage(APacket *pck, ISocket::Protocol proto)
	{
		this->_sendQueue.push(std::make_pair(pck, proto));
	}
}