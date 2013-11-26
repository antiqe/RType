#ifndef __PLAYER_HH__
#define __PLAYER_HH__

#include "ITimer.hpp"
#include "IMutex.hpp"
#include "Client.hpp"

class Account;
class Player
{
public:
  enum StatePlayer
    {
      NONE	= 1,
      READY	= 2,
      LEFT	= 3
    };
private:
  int _id;
  struct sockaddr_in _uinfo;
  Account *_acc;
  char _ship;
  long _latency;
  StatePlayer _state;
  Ultra::ITimer *_lping;
  Ultra::IMutex *_mutex;
public:
  Player(int const id, Account *acc);
  Account *getAccount() const;
  void setAccount(Account *acc);
  char getState() const;
  void setState(StatePlayer const state);
  char getShip() const;
  void setShip(char const ship);
  int getID() const;
  void setID(int const id);
  void setUInfo(struct sockaddr_in const &uinfo);
  struct sockaddr_in const &getUInfo() const;
  long getLatency() const;
  void startTimer();
  void stopTimer();
};

#endif