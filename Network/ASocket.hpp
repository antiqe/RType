#ifndef __ASOCKET_HPP__
#define __ASOCKET_HPP__

#include "ISocket.hpp"
#include <iostream>

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#else
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#endif

class ASocket : public ISocket
{
public:
	virtual ~ASocket() {};
	virtual int  socket(const ISocket::Protocol type) = 0;
	virtual int  accept(int socket, struct sockaddr_in *s_in_client, unsigned int *s_in_size) = 0;
	virtual bool send(int fd, char *msg, size_t length) = 0;
	virtual int  receive(int fd, char *msg, size_t length) = 0;
	virtual bool sendto(int fd, char *msg, size_t length, const struct sockaddr *dest_addr, socklen_t addrlen) = 0;
	virtual int receivefrom(int fd, char *msg, size_t length, struct sockaddr *addr, socklen_t *addrlen) = 0;
	virtual bool connect(int fd, struct sockaddr_in *s_in_server) = 0;
	virtual bool bind(int socket, struct sockaddr_in *s_in);
	virtual bool listen(int socket, int nbClient);
};

#endif