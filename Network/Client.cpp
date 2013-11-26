
#include "ASocket.hpp"
#include "Client.hpp"

#ifdef _WIN32
# include "WSocket.hpp"
#else
# include "LSocket.hpp"
#endif

Network::Client::Client(const std::string &host, const unsigned short port)
	:  _is_connect(false), _is_init(false), _sizesin(0)
{
	_sock[0] = -1;
	_sock[1] = -1;
#ifdef _WIN32
	_socket = new WSocket();
#else
	_socket = new LSocket();
#endif
	struct hostent *shost;

	if ((shost = gethostbyname(host.c_str())))
	{
		_s_in.sin_addr = *(struct in_addr *)shost->h_addr;
		_s_in.sin_port = htons(port);
		_s_in.sin_family = AF_INET;
		_sizesin = sizeof(this->_s_in);
	}
	_is_init = true;
}

bool Network::Client::connect(const ISocket::Protocol type)
{
	if (this->_is_init)
	{
		if (type == ISocket::TCP ||
			type == (ISocket::TCP | ISocket::UDP))
		{
			this->_sock[0] = this->_socket->socket(ISocket::TCP);
			if (_socket->connect(this->_sock[0], &this->_s_in) == false)
			{
			  this->_is_connect = false;
				return (this->_is_connect);
			}
			this->_is_connect = true;
		}
		if (type == ISocket::UDP ||
			type == (ISocket::TCP | ISocket::UDP))
			this->_sock[1] = this->_socket->socket(ISocket::UDP);
	}
	return (this->_is_connect);
}

void Network::Client::disconnect(const ISocket::Protocol type)
{
	if ((type == ISocket::TCP ||
		type == (ISocket::TCP | ISocket::UDP)) && (this->_sock[0] != -1))
		shutdown(this->_sock[0], 2);
	if ((type == ISocket::UDP ||
		type == (ISocket::TCP | ISocket::UDP)) && (this->_sock[1] != -1))
		shutdown(this->_sock[1], 2);
}

short Network::Client::getPort() const
{
  return ((this->_is_init) ? ntohs(this->_s_in.sin_port) : 0);
}

int Network::Client::getSocket(const ISocket::Protocol type) const
{
  return ((type == ISocket::TCP) ? this->_sock[0] : this->_sock[1]);
}

void Network::Client::setSocket(const int socket, const ISocket::Protocol type)
{
  (type == ISocket::TCP) ? this->_sock[0] = socket : this->_sock[1] = socket;
}

const std::string Network::Client::getHost() const
{
  return (inet_ntoa(this->_s_in.sin_addr));
}

void Network::Client::setPort(const unsigned short port)
{
  this->_s_in.sin_port = htons(port);
  this->_sizesin = sizeof(this->_s_in);
}

void Network::Client::setHost(const std::string &host)
{
  struct hostent *shost;
  
  if ((shost = gethostbyname(host.c_str())))
    {
      _s_in.sin_addr = *(struct in_addr *)shost->h_addr;
      _is_init = true;
      _sizesin = sizeof(this->_s_in);
    }
  else
    _is_init = false;
}

bool Network::Client::isConnect() const
{
  return (this->_is_connect);
}

int Network::Client::receive(char* buffer, unsigned short const length,
			     const ISocket::Protocol type)
{
  int		ret;

  ret = (type == ISocket::TCP) ? _socket->receive(this->_sock[0], buffer, length) :
    _socket->receivefrom(this->_sock[1], buffer, length,
			 (struct sockaddr *)&this->_s_in, &this->_sizesin);
  return (ret);
}

bool Network::Client::send(char *buffer, unsigned short const length,
			   const ISocket::Protocol type) const
{
  bool ret;

  ret = false;
  if (type == ISocket::TCP)
    ret = _socket->send(this->_sock[0], buffer, length);
  else
    ret = _socket->sendto(this->_sock[1], buffer, length,
			  (struct sockaddr *)&this->_s_in, this->_sizesin);
  return ret;
}

const struct sockaddr_in &Network::Client::getSockaddr() const
{
  return (this->_s_in);
}

void Network::Client::setSockaddr(struct sockaddr_in const &sockaddr)
{
  this->_s_in = sockaddr;
}

void Network::Client::setSockaddrSize(socklen_t const length)
{
  this->_sizesin = length;
}

const socklen_t &Network::Client::getSockaddrSize() const
{
  return (this->_sizesin);
}
