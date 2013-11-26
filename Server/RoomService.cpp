#include <sstream>

#include "Core.hh"
#include "Room.hh"
#include "IThread.hpp"
#include "RoomService.hh"
#include "ChannelConsole.hh"
#include "TCPPacket.hh"
#include "UDPPacket.hh"

#ifdef _WIN32
#include "WThread.hpp"
#else
#include "LThread.hpp"
#endif

#include "Sleep.hpp"

RoomService::RoomService()
  : _run(false), _log("RoomService")
{
  _log.addChannel(new Logging::ChannelConsole);
  _mfuncTCP[Message::ROOM_CREATE] = &RoomService::onRoomCreate;
  _mfuncTCP[Message::ROOM_JOIN] = &RoomService::onRoomJoin;
  _mfuncTCP[Message::ROOM_LIST] = &RoomService::onRoomList;
  _mfuncTCP[Message::ROOM_TALK] = &RoomService::onRoomTalk;
  _mfuncTCP[Message::ROOM_PLAYER_INFO] = &RoomService::onRoomPlayerInfo;
}

void RoomService::start()
{
  InternalMessage *imsg;

  this->_run = true;
  Logging::Message l("Service is running...", "RoomService", Logging::Message::NOTICE);
  this->_log << l;
  while (this->_run)
    {
      while (!this->_q.isEmpty())
	{
	  imsg = this->_q.pop();
	  APacket *pck = imsg->getPacket();
	  Message *msg = reinterpret_cast<Message *>(pck->getData());
	  if (imsg->getProto() == ISocket::TCP)
	    (this->*_mfuncTCP[msg->getID()])(imsg->getFromTCP(), msg);
	  else
	    {
	      unsigned short id_room;
		  unsigned short id;
	      UDPPacket *pudp = reinterpret_cast<UDPPacket *>(pck);
		  UDPPacket::unpackID(pudp->getID(), id_room, id);
	      Room *room = Core::room_manager->getRoom(id_room);
	      if (room)
			room->notify(new InternalMessage(pudp, imsg->getFromUDP()));
	    }

	}
           Ultra::Sleep::usleep(300);
    }
}

void RoomService::notify(InternalMessage *msg)
{
  this->_q.push(msg);
}

void RoomService::stop()
{
  this->_run = false;
}

void RoomService::onRoomCreate(int const to, Message *msg)
{
  Account *acc = Core::acc_manager->getAccount(to);

  if (acc)
    {
      Room *room;
      std::string name;
      std::string password;

      name = msg->getAttr<std::string>(std::string("name"));
      password = msg->getAttr<std::string>(std::string("password"));
      room = Core::room_manager->createRoom(name, password);
      room->addPlayer(new Player(to, acc));
      acc->setRoom(room);

      Message *rmsg = new Message(Message::ROOM_STATE);
      InternalMessage *imsg = new InternalMessage(new TCPPacket(rmsg, 0), to);
      imsg->addReceiver(to);
      rmsg->setAttr("id", Ultra::Value((unsigned short)room->getID()));
      rmsg->setAttr("state", Ultra::Value((char)Room::OK));

      std::stringstream ss;
      
      ss << room->getID();

      Logging::Message lm("Room create [id = " + ss.str() + ']', "RoomService", Logging::Message::DEBUG);
      this->_log << lm;

      Core::srv_manager->notifyService(ServiceManager::DISPATCH, imsg);
    }
}

void RoomService::onRoomList(int const to, Message *msg)
{
  InternalMessage *imsg = new InternalMessage(new TCPPacket(msg, 0), to);
  Core::room_manager->notifyAll(imsg);
}

void RoomService::onRoomTalk(int const to, Message *msg)
{
	Account *acc = Core::acc_manager->getAccount(to);
	
	if (acc)
	{
		Room *room = acc->getRoom();
		if (room)
			room->notify(new InternalMessage(new TCPPacket(msg), to));
	}
}

void RoomService::onRoomPlayerInfo(int const to, Message *msg)
{
	Account *acc = Core::acc_manager->getAccount(to);
	
	if (acc)
	{
		Room *room = acc->getRoom();
		if (room)
		{
			char state = msg->getAttr<char>("state");
			if (state == Player::LEFT && room->getCurrentPlayer() == 1)
			{
				std::stringstream ss;
				ss << room->getID();
				Core::room_manager->deleteRoom(room->getID());
				Logging::Message lm("Room deleted [id = " + ss.str() + ']', "RoomService", Logging::Message::DEBUG);
				this->_log << lm;
			}
			else
				room->notify(new InternalMessage(new TCPPacket(msg), to));

		}
	}
}

void RoomService::onRoomJoin(int const to, Message *msg)
{
  Account *acc = Core::acc_manager->getAccount(to);

  if (acc)
    {
      unsigned short id = msg->getAttr<unsigned short>("id");
      Room *room = Core::room_manager->getRoom(id);
	  if (room)
		{
		  acc->setRoom(room);
		  std::string password = msg->getAttr<std::string>("password");
		  Message *rmsg = new Message(Message::ROOM_STATE);
		  InternalMessage *imsg = new InternalMessage(new TCPPacket(rmsg, 0), to);
		  imsg->addReceiver(to);
		  rmsg->setAttr("id", Ultra::Value((unsigned short)id));
		  if (room->getPassword() == password)
			{
				if (room->isReachable())
				{
				  rmsg->setAttr("state", Ultra::Value(Room::OK));
				  room->notify(new InternalMessage(new TCPPacket(msg, 0), to));
				}
			  else
				rmsg->setAttr("state", Ultra::Value(Room::LIMIT));
			}
		  else
			rmsg->setAttr("state", Ultra::Value((char)Room::KO));
		  Core::srv_manager->notifyService(ServiceManager::DISPATCH, imsg);
		}
    }
}
