#ifndef __CLIENT_HPP__
#define __CLIENT_HPP__

#include <iostream>
#include "ISocket.hpp"

namespace Network
{
  class Client
  {
  private:
    ISocket				*_socket;
    int					_sock[2];
    bool				_is_connect;
    bool				_is_init;
    std::string			host;
    socklen_t			_sizesin;
    struct sockaddr_in	_s_in;
    
  public:
    Client(const std::string &host, const unsigned short port);
    bool	connect(const ISocket::Protocol type = ISocket::TCP);
    void	disconnect(const ISocket::Protocol type = ISocket::TCP);
    short	getPort() const;
    int		getSocket(const ISocket::Protocol type = ISocket::TCP) const;
    void	setSocket(const int socket, const ISocket::Protocol type = ISocket::TCP);
    const	std::string getHost() const;
    void	setPort(const unsigned short port);
    void	setHost(const std::string &host);

    const struct sockaddr_in &getSockaddr() const;
    const	socklen_t &getSockaddrSize() const;

    void	setSockaddr(struct sockaddr_in const &sockaddr);
    void	setSockaddrSize(socklen_t const length);

    bool	isConnect() const;
    int		receive(char *buffer, unsigned short const length,
			const ISocket::Protocol type = ISocket::TCP);
    bool	send(char *buffer, unsigned short const length,
		     const ISocket::Protocol type = ISocket::TCP) const;
  };
};

#endif // __CLIENT_HPP__
