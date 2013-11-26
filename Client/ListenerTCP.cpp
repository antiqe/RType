#include "ScopeLock.hpp"
#include "ListenerTCP.hpp"
#include "TCPPacket.hpp"
#include "UDPPacket.hpp"

#ifdef _WIN32
#include "WMutex.hpp"
#else
#include "LMutex.hpp"
#endif

ListenerTCP::ListenerTCP(Network::Client * client)
	: _client(client), _run(false)
{
#ifdef _WIN32
	_mutex = new Ultra::WMutex();
#else
	_mutex = new Ultra::LMutex();
#endif
}

ListenerTCP::~ListenerTCP()
{

}

bool ListenerTCP::start()
{
	int ret;
	char buffer[1024];

	this->_run = true;
	APacket *packet = new TCPPacket();
	while (true)
	{
		if ((ret = this->_client->receive(buffer, 1024)) <= 0)
		{
			this->_run = false;
			return (0);
		}
		this->_agg.integrity(ret, buffer, packet);
		while (!this->_agg.isEmpty())
		{
			packet->unpack(this->_agg.getMsgFront().first, this->_agg.getMsgFront().second);
			this->_agg.popMsg();
			this->_mutex->lock();
			Message *msg = reinterpret_cast<Message *>(packet->getData());
			this->_q.push(msg);
			this->_mutex->unlock();
		}
	}	
	return true;
}

bool ListenerTCP::isEmpty()
{
	Ultra::ScopeLock sl(this->_mutex);

	return (this->_q.empty());
}

Message *ListenerTCP::getMessage()
{
	Ultra::ScopeLock sl(this->_mutex);
	Message *msg;

	msg = this->_q.front();
	this->_q.pop();

	return msg;
}

void *ListenerTCP::run(void *listener)
{
	ListenerTCP *ltcp = reinterpret_cast<ListenerTCP *>(listener);

	if (ltcp)
		ltcp->start();
	return 0;
}

bool ListenerTCP::isRunning() const
{
	Ultra::ScopeLock sl(this->_mutex);

	return (this->_run);
}

void ListenerTCP::setRunning(bool state)
{
	Ultra::ScopeLock sl(this->_mutex);

	this->_run = state;
}
