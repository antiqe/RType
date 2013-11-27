#ifndef __ROOM_HH__
#define __ROOM_HH__

#include <vector>
#include <string>
#include <functional>

#include "Player.hh"
#include "IMutex.hpp"
#include "Message.hpp"
#include "UDPPacket.hh"
#include "InternalMessage.hh"
#include "SafeQueue.hpp"

class Account;
class Room
{
public:

  enum State
  {
      OK	= 1,
      KO    = 2,
      LIMIT	= 3
  };

  enum StateRoom
  {
	READY		= 1,
	REACHABLE	= 2,
	RUNNING		= 3
  };

private:
  Ultra::IMutex *_mutex;
  SafeQueue<InternalMessage *> _q;
  typedef std::map<int, Player *> ListPlayer;
  ListPlayer _lplayer;
  StateRoom _stateRoom;
  typedef void (Room::*MsgFuncTCP)(int const to, Message *msg);
  typedef void (Room::*MsgFuncUDP)(InternalMessage *msg);
  MsgFuncTCP _mfuncTCP[Message::COUNT];
  MsgFuncUDP _mfuncUDP[Message::COUNT];
  unsigned short _id;
  std::string _name;
  std::string _password;
  unsigned char _cur;
  unsigned char _max;

public:

  Room(unsigned short const id, std::string const &name, std::string const &password = "");
  unsigned short getID() const;
  std::string getPassword() const;
  void addPlayer(Player *player);
  Player *getPlayer(int const to);
  void delPlayer(int const to);
  static void *run(void *room);
  void notify(InternalMessage *msg);
  bool isReachable() const;
  unsigned char getCurrentPlayer() const;
  int getIDMaster() const;
  ListPlayer::iterator getLastPlayer();
  void kickAll();

private:

  void start();
  void onJoin(int const to, Message *msg);
  void onInfo(int const to, Message *msg);
  void onPlayerInfo(int const to, Message *msg);
  void onPing(InternalMessage *imsg);
  void onPlayerInfoInGame(InternalMessage *imsg);
  void onPlayerTalk(int const to, Message *msg);
  void onCreate(int const to, Message *msg);
  void onKick(int const to, Message *msg);
  void onStart(int const to, Message *msg);
};

#endif