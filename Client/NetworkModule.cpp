
#include <sstream>

#include "State.hpp"
#include "NetworkModule.hpp"
#include "Singleton.hpp"
#include "Core.hpp"
#include "TCPPacket.hpp"
#include "ScopeLock.hpp"
#include "ListenerTCP.hpp"
#include "NetworkEvent.hpp"
#include "Message.hpp"

#ifdef _WIN32
#include "WThread.hpp"
#else
#include "LThread.hpp"
#endif

NetworkModule::NetworkModule()
  : Engine::ANetworkModule(), _client(0), _ltcp(0), _thread(0), _stateModule(0), _msgTreat(10)
{
#ifdef _WIN32
	this->_thread = new Ultra::WThread();
#else
	this->_thread = new Ultra::LThread();
#endif
}

NetworkModule::~NetworkModule()
{
	delete this->_thread;
}

bool	NetworkModule::start()
{
	if (this->_port && !this->_host.empty())
	{
		this->_client = new Network::Client(this->_host, this->_port);
		if (this->_client->connect())
		{
			this->_sock =  this->_client->getSocket(ISocket::TCP);
			this->_ltcp = new ListenerTCP(_client);
			this->_ltcp->setRunning(true);
			this->_thread->create(ListenerTCP::run, this->_ltcp);
			this->_started = true;
		}
		else
			this->_started = false;
	}
	return (this->_started);
}

void	NetworkModule::initialize()
{
	if (this->_owner)
		this->_stateModule = dynamic_cast<StateModule *>(this->_owner->getModule(Engine::AModule::STATE));;
}

void	NetworkModule::update()
{
	if (this->_started)
	{
		if (this->_ltcp && !this->_ltcp->isRunning())
		{
			Engine::AStateModule* stateModule = dynamic_cast<Engine::AStateModule*>(Engine::Core::getInstance()->getModule(Engine::AModule::STATE));
			Ultra::ScopeLock lock(Engine::Core::getInstance()->access(Engine::AModule::STATE));
			stateModule->popTo(State::CONNECTION);
			this->_started = false;
		}
		for (int i = 0; !this->_sendQueue.empty() && i < this->_msgTreat; ++i)
		{
			std::pair<APacket *, ISocket::Protocol> p = this->_sendQueue.front();
			if (p.second == ISocket::TCP)
			{
				unsigned short length = 0;
				char *data = p.first->pack(length);
				std::cout << "Send!" << std::endl;
			    this->_client->send(data, length);
			}
			//else
				//this->_client->send(data, length, ISocket::UDP);
			this->_sendQueue.pop();
		}

		while (!this->_ltcp->isEmpty())
			this->_recvQueue.push(this->_ltcp->getMessage());
		
		//Ultra::ScopeLock	lock(Engine::Core::getInstance()->access(AModule::STATE));
		Engine::AState*		state = !this->_stateModule ? 0 : this->_stateModule->top();

		for (int i = 0; !this->_recvQueue.empty() && i < _msgTreat; ++i)
		{
			Message *msg = this->_recvQueue.front();
			std::cout << "Receive MSG [ID=" << msg->getID() << "]" << std::endl;
			std::stringstream ss;
			ss << msg->getID();
			if (state)
				state->dispatchEvent(new Engine::NetworkEvent(ss.str(), msg));
			delete msg;
			this->_recvQueue.pop();
		}
	}
}

void	NetworkModule::unload()
{
	this->stop();
}

void	NetworkModule::stop()
{
	if (this->_started == true)
	{
		this->_started = false;
		this->_client->disconnect();
		this->_thread->exit();
		delete this->_ltcp;
		delete this->_client;
		this->_ltcp = 0;
		this->_client = 0;
		this->_port = 0;
		this->_host = "";
	}
}

int	NetworkModule::getSock() const
{
	return (this->_sock);
}