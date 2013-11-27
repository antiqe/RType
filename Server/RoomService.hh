#ifndef __ROOMSERVICE_HH__
#define __ROOMSERVICE_HH__

#include "Logger.hpp"

#include "Message.hpp"
#include "InternalMessage.hh"
#include "IService.hh"
#include "SafeQueue.hpp"

class RoomService : public IService
{
private:
  SafeQueue<InternalMessage *> _q;
  typedef void (RoomService::*MsgFuncTCP)(int const to, Message *msg);
  MsgFuncTCP _mfuncTCP[Message::COUNT];
  bool _run;
  Logging::Logger _log;
public:
  RoomService();
  virtual void start();
  virtual void stop();
  virtual void notify(InternalMessage *msg);
  static void  *execRoomList(void *data);
private:
  void  onRoomCreate(int const to, Message *msg);
  void  onRoomJoin(int const to, Message *msg);
  void  onRoomList(int const to, Message *msg);
  void  onRoomPlayerInfo(int const to, Message *msg);
  void  onRoomPlayers(int const to, Message *msg);
  void  onRoomTalk(int const to, Message *msg);
  void	onRoomStart(int const to, Message *msg);
};

#endif