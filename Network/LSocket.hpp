
#ifndef __LSOCKET_HPP__
#define __LSOCKET_HPP__

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <ostream>

#include "ASocket.hpp"

class LSocket : public ASocket
{
public:
	LSocket();
	~LSocket();
	int	socket(const ISocket::Protocol type);
	int  accept(int socket, struct sockaddr_in *s_in_client, unsigned int *s_in_size);
	bool send(int fd, char *msg, size_t length);
	int receive(int fd, char *msg, size_t length);
	bool sendto(int fd, char *msg, size_t length, const struct sockaddr *dest_addr, socklen_t addrlen);
	int receivefrom(int fd, char *msg, size_t length, struct sockaddr *addr, socklen_t *addrlen);
	bool connect(int fd, struct sockaddr_in *s_in_server);
};

#endif // __LSOCKET_HPP__
