
#ifndef __WSOCKET_HPP__
#define __WSOCKET_HPP__

#include <iostream>

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib")
#endif

#include "ASocket.hpp"

class WSocket : public ASocket
{
	WSAData				_data;
	WSAOVERLAPPED		_SendOverlapped;
	WSAOVERLAPPED		_RecvOverlapped;

public:
  WSocket();
  ~WSocket();
  int  socket(const ISocket::Protocol type);
  int  accept(int socket, struct sockaddr_in *s_in_client, unsigned int *s_in_size);
  bool send(int fd, char *msg, size_t length);
  int  receive(int fd, char *msg, size_t length);
  bool sendto(int fd, char *msg, size_t length, const struct sockaddr *addr, socklen_t addrlen);
  int  receivefrom(int fd, char *msg, size_t length, struct sockaddr *addr, socklen_t *addrlen);
  bool connect(int fd, struct sockaddr_in *s_in_server);
};

#endif // __WSOCKET_HPP__
