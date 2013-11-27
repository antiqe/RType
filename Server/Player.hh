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
	enum StateSpecPlayer
	{
		MASTER = 1,
		SIMPLE = 2
	};
private:
  char _rank;
  int _id;
  struct sockaddr_in _uinfo;
  Account *_acc;
  char _ship;
  long _latency;
  StateSpecPlayer _stateSpec;
  StatePlayer _state;
  Ultra::ITimer *_lping;
  Ultra::IMutex *_mutex;
public:
	Player(char const rank, int const id, Account *acc, StateSpecPlayer const state = SIMPLE);
  Account *getAccount() const;
  void setAccount(Account *acc);
  char getState() const;
  void setState(StatePlayer const state);
  void setStateSpec(StateSpecPlayer const state);
  char getStateSpec() const;
  char getShip() const;
  void setShip(char const ship);
  int getID() const;
  void setID(int const id);
  void setUInfo(struct sockaddr_in const &uinfo);
  struct sockaddr_in const &getUInfo() const;
  long getLatency() const;
  void startTimer();
  void stopTimer();
  void setRank(char const rank);
  char getRank() const;
};

#endif