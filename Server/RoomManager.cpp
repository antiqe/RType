#include "Room.hh"
#include "Pool.hpp"
#include "RoomManager.hh"
#include "ChannelConsole.hh"
#include "ScopeLock.hpp"

#ifdef _WIN32
#include "WMutex.hpp"
#include "WThread.hpp"
#else
#include "LMutex.hpp"
#include "LThread.hpp"
#endif

RoomManager::RoomManager()
  : _id(1), _log("RoomManager")
{
  _log.addChannel(new Logging::ChannelConsole);
#ifdef _WIN32
  _mutex = new Ultra::WMutex();
#else
  _mutex = new Ultra::LMutex();
#endif
}

Room *RoomManager::createRoom(std::string const &name, std::string const &password)
{
  Ultra::ScopeLock sl(this->_mutex);
  
  unsigned short id;
  
  if (!this->_idq.empty())
    {
      this->_idq.pop();
      id = this->_idq.front();
    }
  else
    {
      id = this->_id;
      this->_id++;
    }
  Room *room = new Room(id, name, password);
  this->_mroom[id] = room;
  
  Ultra::IThread *cthread = 0;  
#ifdef _WIN32
  cthread = new Ultra::WThread();
#else
  cthread = new Ultra::LThread();
#endif
  
  cthread->create(&Room::run, room);
  return (room);
}

void RoomManager::deleteRoom(unsigned short const id)
{
    Ultra::ScopeLock sl(this->_mutex);

	this->_idq.push(id);
	this->_mroom.erase(id);
}

void RoomManager::run()
{
  
}

Room *RoomManager::getRoom(unsigned short const id)
{
  Ultra::ScopeLock sl(this->_mutex);

  return (this->_mroom[id]);
}

void RoomManager::notifyAll(InternalMessage *msg)
{
  Ultra::ScopeLock sl(this->_mutex);

  std::map<unsigned short, Room *>::iterator it = this->_mroom.begin();
  for (; it != this->_mroom.end(); ++it)
    it->second->notify(msg);
}
