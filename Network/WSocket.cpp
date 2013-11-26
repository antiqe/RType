
#include "WSocket.hpp"

WSocket::WSocket()
{
	if (WSAStartup((WORD)2.2, &_data) == -1)
	{
		std::cerr << "WSAStartup has failed." << std::endl;
	}
	if ((_RecvOverlapped.hEvent = WSACreateEvent()) == NULL)
	{
		std::cout << "WSACreateEvent failed" << std::endl;
	}
	if ((_SendOverlapped.hEvent = WSACreateEvent()) == NULL)
	{
		std::cout << "WSACreateEvent failed" << std::endl;
	}
}

WSocket::~WSocket()
{
	WSACloseEvent(_RecvOverlapped.hEvent);
	WSACloseEvent(_SendOverlapped.hEvent);
	WSACleanup();
}

int WSocket::socket(const ISocket::Protocol type)
{
	SOCKET	socket;


	if (type == ISocket::TCP)
		socket = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED);
	else
		socket = WSASocket(AF_INET, SOCK_DGRAM, IPPROTO_UDP, NULL, 0, 0);
	if (socket ==  INVALID_SOCKET)
		std::cout << "Socket has failed" << std::endl;
	return socket;
}

int WSocket::accept(int socket, struct sockaddr_in *s_in_client, unsigned int *s_in_size)
{
	int fd;

	if ((fd = WSAAccept(socket,(struct sockaddr *)s_in_client, (socklen_t *)s_in_size, NULL, NULL)) == -1)
	{
		std::cerr << "Accept has failed." << std::endl;
	}
	return (fd);
}

bool WSocket::send(int fd, char *msg, size_t length)
{
  WSABUF DataBuf;

  DataBuf.len = length;
  DataBuf.buf = msg;

  DWORD SendBytes;
  if (WSASend(fd, &DataBuf, 1, &SendBytes, 0, 0, 0) == SOCKET_ERROR)
      return false;
  return true;
}

int WSocket::receive(int fd, char *msg, size_t length)
{
  WSABUF	DataBuf;

  DataBuf.buf = new char[length + 1];
  DataBuf.len = length;

  DWORD RendBytes, flags;
  flags = 0;
  if ((WSARecv(fd, &DataBuf, 1, &RendBytes, &flags, 0 , 0)) == SOCKET_ERROR)
    return 0;
  memcpy(msg, DataBuf.buf, RendBytes);
  return RendBytes;
}


bool	WSocket::sendto(int fd, char *msg, size_t length, const struct sockaddr *addr, socklen_t addrlen)
{
  WSABUF DataBuf;

  DataBuf.len = length;
  DataBuf.buf = msg;

  DWORD SendBytes;
  SecureZeroMemory((PVOID) &_SendOverlapped, sizeof (WSAOVERLAPPED));
  if (WSASendTo(fd, &DataBuf, 1, &SendBytes, 0, addr,
		addrlen, &_SendOverlapped, NULL) == SOCKET_ERROR)
    return false;
  return true;
}

int	WSocket::receivefrom(int fd, char *msg, size_t length, struct sockaddr *addr, socklen_t *addrlen)
{
  WSABUF	DataBuf;

  DataBuf.buf = new char[length + 1];
  DataBuf.len = length;

  DWORD RendBytes, flags;
  SecureZeroMemory((PVOID) & _RecvOverlapped, sizeof (WSAOVERLAPPED));
  flags = 0;
  if ((WSARecvFrom(fd, &DataBuf, 1, &RendBytes, &flags, addr,
		   addrlen, &_RecvOverlapped, NULL)) == SOCKET_ERROR)
  {
	  delete DataBuf.buf;
	  return 0;
  }
  DataBuf.buf[RendBytes] = 0;
  memcpy(msg, DataBuf.buf, RendBytes);
  return RendBytes;
}

bool WSocket::connect(int fd, struct sockaddr_in *s_in_server)
{
  if (::connect(fd, (struct sockaddr *)s_in_server, sizeof(*s_in_server)) == -1)
    return false;
  return true;
}
