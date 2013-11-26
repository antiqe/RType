//#include <unistd.h>

#include "Core.hh"
#include "Room.hh"
#include "Sleep.hpp"
#include "Account.hh"
#include "TCPPacket.hh"
#include "ScopeLock.hpp"

#ifdef _WIN32
#include "WMutex.hpp"
#else
#include <ctime>
#include "LMutex.hpp"
#endif

Room::Room(unsigned short const id, std::string const &name, std::string const &password)
	: _stateRoom(Room::REACHABLE), _id(id), _name(name), _password(password), _max(4)
{
  this->_mfuncTCP[Message::ROOM_JOIN] = &Room::onJoin;
  this->_mfuncTCP[Message::ROOM_LIST] = &Room::onInfo;
  this->_mfuncTCP[Message::ROOM_TALK] = &Room::onPlayerTalk;
  this->_mfuncTCP[Message::ROOM_PLAYER_INFO] = &Room::onPlayerInfo;
  this->_mfuncUDP[Message::GAME_PING] = &Room::onPing;
  this->_mfuncUDP[Message::ROOM_PLAYER_INFO] = &Room::onPlayerInfoInGame;
#ifdef _WIN32
  _mutex = new Ultra::WMutex();
#else
  _mutex = new Ultra::LMutex();
#endif
}

void *Room::run(void *data)
{
  Room *room = reinterpret_cast<Room *>(data);

  room->start();
  return (0);
}

void Room::start()
{
  InternalMessage *imsg;

  while (true)
    {
      while (!this->_q.isEmpty())
	{
	  imsg = this->_q.pop();
	  APacket *pck = imsg->getPacket();
	  Message *msg = reinterpret_cast<Message *>(pck->getData());
	  if (imsg->getProto() == ISocket::TCP)
	    (this->*_mfuncTCP[msg->getID()])(imsg->getFromTCP(), msg);
	  else
	    (this->*_mfuncUDP[msg->getID()])(imsg);
	}
		Ultra::Sleep::usleep(300);
    }
}

void Room::addPlayer(Player *player)
{
  Ultra::ScopeLock sl(this->_mutex);

  this->_lplayer[player->getID()] = player;
}

unsigned short Room::getID() const
{
  Ultra::ScopeLock sl(this->_mutex);

  return (this->_id);
}

std::string Room::getPassword() const
{
  Ultra::ScopeLock sl(this->_mutex);

  return (this->_password);
}

void Room::notify(InternalMessage *msg)
{
  this->_q.push(msg);
}

void Room::delPlayer(int const to)
{
  Ultra::ScopeLock sl(this->_mutex);

  Room::ListPlayer::iterator it = this->_lplayer.find(to);
  if (it != this->_lplayer.end())
    this->_lplayer.erase(it);
}

Player *Room::getPlayer(const int to)
{
  Ultra::ScopeLock sl(this->_mutex);

  return (this->_lplayer[to]);
}

void Room::onInfo(int const to, Message *)
{
	if (this->_stateRoom == Room::REACHABLE)
	{
	  Message *rmsg = new Message(Message::ROOM_INFO);
	  InternalMessage *imsg = new InternalMessage(new TCPPacket(rmsg, 0), to);
	  imsg->addReceiver(to);

	  rmsg->setAttr("id", Ultra::Value((unsigned short)this->_id));
	  rmsg->setAttr("name", Ultra::Value(std::string(this->_name)));
	  rmsg->setAttr("private", Ultra::Value((this->_password == "" ? false : true)));
	  rmsg->setAttr("cur_player", Ultra::Value((char)_lplayer.size()));
	  rmsg->setAttr("max_player", Ultra::Value((char)this->_max));

	  Core::srv_manager->notifyService(ServiceManager::DISPATCH, imsg);
	}
}

void Room::onPlayerInfo(int const to, Message *msg)
{
  Account *acc = Core::acc_manager->getAccount(to);
  
  if (acc)
    {
      char state = msg->getAttr<char>("state");
      Player *player = this->getPlayer(to);
      if (player)
	{
	  player->setState((Player::StatePlayer)(state));
	  InternalMessage *imsg = new InternalMessage(new TCPPacket(msg, 0), 0);
	  this->_mutex->lock();
	  for (Room::ListPlayer::iterator it = this->_lplayer.begin(); it != this->_lplayer.end(); ++it)
	    imsg->addReceiver(it->second->getID());
	  this->_mutex->unlock();
	  if (state == Player::LEFT)
	    this->delPlayer(to);
	  else
	  {
		  this->_mutex->lock();
		  Room::ListPlayer::iterator it = this->_lplayer.begin();
		  for (; it != this->_lplayer.end() && it->second->getState() == Player::READY; ++it);
		  if (it == this->_lplayer.end() || this->_stateRoom == Room::READY)
		  {
			  this->_stateRoom = (this->_stateRoom != Room::READY) ? Room::READY : Room::REACHABLE;
			  Message *msg = new Message(Message::GAME_START);
			  InternalMessage *readymsg = new InternalMessage(new TCPPacket(msg, 0), 0);
			  readymsg->addReceiver(this->_lplayer.begin()->second->getID());
			  Core::srv_manager->notifyService(ServiceManager::DISPATCH, readymsg);
		  }
		  this->_mutex->unlock();
	  }
	  Core::srv_manager->notifyService(ServiceManager::DISPATCH, imsg);
	}
    }
}

void Room::onPlayerTalk(int const to, Message *msg)
{
	Ultra::ScopeLock sl(this->_mutex);

	InternalMessage *imsg = new InternalMessage(new TCPPacket(msg, 0), 0);
	
	for (Room::ListPlayer::iterator it = this->_lplayer.begin(); it != this->_lplayer.end(); ++it)
	    imsg->addReceiver(it->second->getID());

	Core::srv_manager->notifyService(ServiceManager::DISPATCH, imsg);
}

void Room::onPing(InternalMessage *imsg)
{
  unsigned short room;
  unsigned short id;
  UDPPacket *packet = reinterpret_cast<UDPPacket *>(imsg->getPacket());
  UDPPacket::unpackID(packet->getID(), room, id);
  Player *player = this->getPlayer(id);

  if (player)
    {
	  player->setUInfo(imsg->getFromUDP());
      player->stopTimer();
    }
}

void Room::onPlayerInfoInGame(InternalMessage *imsg)
{
	(void)imsg;
	/*UDPPacket *packet = reinterpret_cast<UDPPacket *>(imsg->getPacket());
	Message *msg = reinterpret_cast<Message *>(packet->getData());

	if (msg)
	{
		InternalMessage *rmsg = new InternalMessage(new UDPPacket(msg, 0, 0, 0), 0);
		this->_mutex->lock();
		for (Room::ListPlayer::iterator it = this->_lplayer.begin(); it != this->_lplayer.end(); ++it)
			imsg->addReceiver(it->second->getUInfo());
		this->_mutex->unlock();
		Core::srv_manager->notifyService(ServiceManager::DISPATCH, imsg);
		
	}*/
}

void Room::onJoin(int const to, Message *)
{
  Account *acc = Core::acc_manager->getAccount(to);

  if (acc)
    {
      Player *player = new Player(to, acc);
      this->addPlayer(player);
      
      Message *rmsg = new Message(Message::ROOM_PLAYER_INFO);
      InternalMessage *imsg = new InternalMessage(new TCPPacket(rmsg, 0), 0);
      rmsg->setAttr("id_player", Ultra::Value((char)this->_lplayer.size()));
      rmsg->setAttr("name", Ultra::Value(acc->getLogin()));
      rmsg->setAttr("id_ship", Ultra::Value((char)player->getShip()));
      rmsg->setAttr("state", Ultra::Value((char)player->getState()));

      this->_mutex->lock();
      for (Room::ListPlayer::iterator it = this->_lplayer.begin(); it != this->_lplayer.end(); ++it)
		imsg->addReceiver(it->second->getID());
      this->_mutex->unlock();

      Core::srv_manager->notifyService(ServiceManager::DISPATCH, imsg);

      Message *amsg = new Message(Message::ROOM_PLAYER_INFO);
      InternalMessage *iamsg = new InternalMessage(new TCPPacket(amsg, 0), to);
      iamsg->addReceiver(to);
      this->_mutex->lock();
      for (Room::ListPlayer::iterator it = this->_lplayer.begin(); it != this->_lplayer.end(); ++it)
		{
			if (it->second->getID() != to)
				{
				  amsg->setAttr("id_player", Ultra::Value((char)(std::distance(this->_lplayer.begin(), it) + 1)));
				  amsg->setAttr("name", Ultra::Value(it->second->getAccount()->getLogin()));
				  amsg->setAttr("id_ship", Ultra::Value(it->second->getShip()));
				  amsg->setAttr("state", Ultra::Value(it->second->getState()));
				  Core::srv_manager->notifyService(ServiceManager::DISPATCH, iamsg);
				}
		}
      this->_mutex->unlock();
    }
}

bool Room::isReachable() const
{
  Ultra::ScopeLock sl(this->_mutex);  

  return (this->_lplayer.size() < this->_max ? true : false);
}

unsigned char Room::getCurrentPlayer() const
{
	Ultra::ScopeLock sl(this->_mutex);  

	return (this->_lplayer.size());
}