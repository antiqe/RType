
#ifndef __SERVER_HPP__
#define __SERVER_HPP__

#include "ISocket.hpp"
#include "Client.hpp"

namespace Network
{
	class Server
	{
	private:
		ISocket				*_socket;
		bool				_is_run;
		int					_sock[2];
		struct sockaddr_in	_s_in;

	public:
		Server(unsigned short port);
		~Server();
		bool			run(unsigned maxClient, const ISocket::Protocol type = ISocket::TCP);
		void			stop();
		unsigned short	getPort() const;
		bool			isRunning() const;
		Network::Client	*acceptConnection();
		int				getSocket(const ISocket::Protocol type = ISocket::TCP);

	};
};
#endif // __ASERVER_HPP__
