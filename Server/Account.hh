//
// Account.hh
// 
// Made by Guiho Ronan
// 
// Started on  Sat Oct 26 20:32:05 2013 Guiho Ronan
// Last update Sat Oct 26 20:34:33 2013 Guiho Ronan
//

#ifndef __ACCOUNT_HH__
#define __ACCOUNT_HH__
 
#include <string>

#include "IMutex.hpp"
#include "Room.hh"

class Account
{
public:
  enum State
    {
      NONE  		= 0,
      ONLINE    	= 1,
      OFFLINE		= 2
    };
private:
  std::string _login;
  std::string _passwd;
  Account::State _state;
  Room *_room;
  Ultra::IMutex *_mutex;
public:
  Account(std::string const &login, std::string const &passwd);
  std::string getPassword() const;
  std::string getLogin() const;
  Account::State getState() const;
  void setState(Account::State const state);
  void setRoom(Room *room);
  Room *getRoom() const;
};

#endif