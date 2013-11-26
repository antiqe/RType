
#include <unistd.h>
#include "LSocket.hpp"

LSocket::LSocket()
{
}

LSocket::~LSocket()
{
}

int	LSocket::socket(const ISocket::Protocol type)
{
  if (type == ISocket::TCP)
    return ::socket(AF_INET, SOCK_STREAM, 0);
  return ::socket(AF_INET, SOCK_DGRAM, 0);
}

int  LSocket::accept(int socket, struct sockaddr_in *s_in_client, unsigned int *s_in_size)
{
  return ::accept(socket, (struct sockaddr *)s_in_client, s_in_size);
}

bool  LSocket::connect(int fd, struct sockaddr_in *s_in_server)
{
  if (::connect(fd, (struct sockaddr *)s_in_server, sizeof(*s_in_server)) == -1)
    {
      return false;
    }
  return true;
}

bool LSocket::send(int fd, char *msg, size_t length)
{
  if (::send(fd, msg, length, MSG_NOSIGNAL) == -1)
    return false;
  return true;
}

int LSocket::receive(int fd, char *msg, size_t length)
{
  int ret;
  
  ret = ::recv(fd, msg, length, MSG_NOSIGNAL);
  return ret;
}

bool	LSocket::sendto(int fd, char *msg, size_t length, const struct sockaddr *addr, socklen_t addrlen)
{
  if (::sendto(fd, msg, length, MSG_NOSIGNAL, addr, addrlen) == -1)
    return false;
  return true;
}

int	LSocket::receivefrom(int fd, char *msg, size_t length, struct sockaddr *addr, socklen_t *addrlen)
{
  int ret;
  
  ret = ::recvfrom(fd, msg, length, MSG_NOSIGNAL, addr, addrlen);
  return ret;
}
