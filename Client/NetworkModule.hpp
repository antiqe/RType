#ifndef _NETWORKMODULE_H_
#define _NETWORKMODULE_H_

#include <queue>
#include <functional>

#include "ISocket.hpp"
#include "IThread.hpp"
#include "ListenerTCP.hpp"
#include "ANetworkModule.hpp"
#include "StateModule.hpp"
#include "Event.hpp"

class NetworkModule : public Engine::ANetworkModule
{
public:
	enum Services
	{
		AUTH = 1,
		ROOM = 2
	};

private:
	int						_sock;
	Network::Client*		_client;
	ListenerTCP*			_ltcp;
	Ultra::IThread*			_thread;
	StateModule*			_stateModule;
	unsigned short			_msgTreat;
	std::queue<Message *>	_recvQueue;
public:
	NetworkModule();
	~NetworkModule();

	void	initialize();
	void	update();
	void	unload();
	bool	start();
	void	stop();

	int		getSock() const;
};

#endif