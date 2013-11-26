#ifndef __ROOMMANAGER_HH__
#define __ROOMMANAGER_HH__

#include <map>
#include <queue>
#include <string>

#include "Room.hh"
#include "Pool.hpp"
#include "IMutex.hpp"
#include "Logger.hpp"
#include "IThread.hpp"
#include "IManager.hh"

class RoomManager : public IManager
{
private:
  unsigned short _id;
  std::queue<int> _idq;
  std::map<unsigned short, Room *> _mroom;
  Logging::Logger _log;
  Ultra::IMutex *_mutex;
public:
  RoomManager();
  Room *createRoom(std::string const &name, std::string const &password = "");
  void deleteRoom(unsigned short const id);
  virtual void run();
  Room *getRoom(unsigned short const id);
  void notifyAll(InternalMessage *msg);
};

#endif