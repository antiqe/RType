
#include <iostream>
#include <string>

#include "Server.hpp"

#ifdef _WIN32
# include "WSocket.hpp"
#else
# include "LSocket.hpp"
#endif

Network::Server::Server(unsigned short port)
	: _socket(NULL), _is_run(false)
{
	_sock[0] = -1;
	_sock[1] = -1;
	_s_in.sin_addr.s_addr = htonl(INADDR_ANY);
	_s_in.sin_family = AF_INET;
	_s_in.sin_port = htons(port);
#ifdef _WIN32
	_socket = new WSocket();
#else
	_socket = new LSocket();
#endif
}

Network::Server::~Server()
{
}

bool	Network::Server::run(unsigned maxClient, const ISocket::Protocol type)
{
	if (type == ISocket::TCP ||
		type == (ISocket::TCP | ISocket::UDP))
	{
		this->_sock[0] =  _socket->socket(type);
		if ((_socket->bind(_sock[0], &_s_in)) == false)
			return (false);
		_socket->listen(_sock[0], maxClient);
	}
	if (type == ISocket::UDP ||
		type == (ISocket::TCP | ISocket::UDP))
	{
		this->_sock[1] =  _socket->socket(type);
		if ((_socket->bind(_sock[1], &_s_in)) == false)
			return (false);
	}
	this->_is_run = true;
	return true;
}

void		Network::Server::stop()
{
	shutdown(this->_sock[0], 2);
	shutdown(this->_sock[1], 2);
}

unsigned short		Network::Server::getPort() const
{
	return (ntohs(this->_s_in.sin_port));
}

bool		Network::Server::isRunning() const
{
	return (this->_is_run);
}

Network::Client		*Network::Server::acceptConnection()
{
	int					sock;
	unsigned			size;
	struct sockaddr_in	cin;
	Network::Client		*client;

	size = sizeof(cin);
	sock = _socket->accept(this->_sock[0], &cin, &size);
	client = new Network::Client(inet_ntoa(cin.sin_addr), this->getPort());
	client->setSocket(sock);
	return (client);
}

int			Network::Server::getSocket(const ISocket::Protocol type)
{
	if (type == ISocket::TCP)
		return this->_sock[0];
	return this->_sock[1];
}
