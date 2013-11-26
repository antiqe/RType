#ifndef __LISTENERTCP_H__
#define __LISTENERTCP_H__

#include <queue>
#include <string>

#include "Client.hpp"
#include "IMutex.hpp"
#include "Message.hpp"
#include "Aggregator.hpp"

class ListenerTCP
{
private:
	Network::Client *_client;
	std::queue<Message *> _q;
	Ultra::IMutex *_mutex;
	Aggregator _agg;
	bool _run;
public:
	ListenerTCP(Network::Client *client);
	~ListenerTCP();
	bool start();
	bool isEmpty();
	Message *getMessage();
	static void *run(void *listener);
	bool isRunning() const;
	void setRunning(bool);
};

#endif