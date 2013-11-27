#include "MessageFactory.hpp"
#include "Message.hpp"

MessageFactory::MessageFactory()
{
  Message msg(0);

  msg.setID(Message::AUTH_AVAILABLE);
  msg.setAttr("state", Ultra::Value((char)0));
  this->learn(Message::AUTH_AVAILABLE, msg);

  msg.clearAttrs();

  msg.setID(Message::AUTH_LOGIN);
  msg.setAttr("login", Ultra::Value(std::string("")));
  msg.setAttr("password", Ultra::Value(std::string("")));
  this->learn(Message::AUTH_LOGIN, msg);

  msg.clearAttrs();

  msg.setID(Message::AUTH_ACCESS);
  msg.setAttr("state", Ultra::Value((char)0));
  this->learn(Message::AUTH_ACCESS, msg);

  msg.clearAttrs();

  msg.setID(Message::ROOM_CREATE);
  msg.setAttr("name", Ultra::Value(std::string("")));
  msg.setAttr("password", Ultra::Value(std::string("")));
  this->learn(Message::ROOM_CREATE, msg);

  msg.clearAttrs();

  msg.setID(Message::ROOM_STATE);
  msg.setAttr("id", Ultra::Value((unsigned short)0));
  msg.setAttr("state", Ultra::Value((char)0));
  this->learn(Message::ROOM_STATE, msg);

  msg.clearAttrs();

  msg.setID(Message::ROOM_JOIN);
  msg.setAttr("id", Ultra::Value((unsigned short)0));
  msg.setAttr("password", Ultra::Value(std::string("")));
  this->learn(Message::ROOM_JOIN, msg);

  msg.clearAttrs();

  msg.setID(Message::ROOM_PLAYER_INFO);
  msg.setAttr("id_player", Ultra::Value((char)0));
  msg.setAttr("name", Ultra::Value(std::string("")));
  msg.setAttr("id_ship", Ultra::Value((char)0));
  msg.setAttr("state", Ultra::Value((char)0));
  this->learn(Message::ROOM_PLAYER_INFO, msg);

  msg.clearAttrs();
  
  msg.setID(Message::ROOM_LIST);
  this->learn(Message::ROOM_LIST, msg);

   msg.clearAttrs();
  
  msg.setID(Message::ROOM_PLAYERS);
  this->learn(Message::ROOM_PLAYERS, msg);

  msg.clearAttrs();

  msg.setID(Message::ROOM_INFO);
  msg.setAttr("id", Ultra::Value((unsigned short)0));
  msg.setAttr("name", Ultra::Value(std::string("")));
  msg.setAttr("private", Ultra::Value(false));
  msg.setAttr("cur_player", Ultra::Value((char)0));
  msg.setAttr("max_player", Ultra::Value((char)0));
  this->learn(Message::ROOM_INFO, msg);

  msg.clearAttrs();

  msg.setID(Message::ROOM_TALK);
  msg.setAttr("from", Ultra::Value(std::string("")));
  msg.setAttr("msg", Ultra::Value(std::string("")));
  this->learn(Message::ROOM_TALK, msg);

  msg.clearAttrs();

  msg.setID(Message::GAME_PING);
  msg.setAttr("id", Ultra::Value((int)0));
  msg.setAttr("time", Ultra::Value((unsigned long int)0));
  this->learn(Message::GAME_PING, msg);
}

MessageFactory::~MessageFactory()
{

}

Message *MessageFactory::createMessage(unsigned short const id) const
{
  return (this->create(id));
}
