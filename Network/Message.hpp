
#ifndef __MESSAGE_HPP__
#define __MESSAGE_HPP__

#include "IMessage.hpp"
#include "IPrototype.hpp"
#include "Value.hpp"
#include "Attr.hpp"
#include "BinaryStream.hpp"

class Message : public IMessage, public Ultra::IPrototype<Message>, public Ultra::Attr
{  
public:
  enum ID
    {
      AUTH_AVAILABLE = 1,
      AUTH_LOGIN,
      AUTH_ACCESS,
      ROOM_CREATE,
      ROOM_STATE,
      ROOM_JOIN,
      ROOM_PLAYER_INFO,
	  ROOM_PLAYERS,
      ROOM_LIST,
      ROOM_INFO,
	  ROOM_TALK,
      ROOM_KICK,
      ROOM_START,
      ROOM_ERROR,
      GAME_START,
      GAME_DATA_LOAD,
      GAME_MOB_CREATE,
      GAME_AGENT,
      GAME_COLLISION,
      GAME_OBJECT_INFO,
      GAME_SHOOT,
      GAME_OBJ_CREATE,
      GAME_PING,
      COUNT
    };

private:

  unsigned short _id;
 
  typedef void (Message::*MethSerialize)(const Ultra::Value &, BinaryStream *);
  std::map<Ultra::Value::Type, MethSerialize> _ptrSerialize;
  typedef Ultra::Value (Message::*MethUnserialize)(BinaryStream *);
  std::map<Ultra::Value::Type, MethUnserialize> _ptrUnserialize;
  
public:

  Message(unsigned short const id);
  ~Message();
  Message(Message const &msg);

  Message &operator=(Message const &msg);

  virtual char	*serialize(unsigned short &length);
  virtual void	unserialize(char *msg, const unsigned int length);

  virtual unsigned short getID() const;
  void setID(unsigned short const id);

  bool operator==(Message const &msg);

  Message *clone() const;
private:

  void  initMap();

  void	serializeChar(const Ultra::Value &value, BinaryStream *bs);
  void	serializeUChar(const Ultra::Value &value, BinaryStream *bs);
  void	serializeShort(const Ultra::Value &value, BinaryStream *bs);
  void	serializeUShort(const Ultra::Value &value, BinaryStream *bs);
  void	serializeInt(const Ultra::Value &value, BinaryStream *bs);
  void	serializeUInt(const Ultra::Value &value, BinaryStream *bs);
  void	serializeLong(const Ultra::Value &value, BinaryStream *bs);
  void	serializeULong(const Ultra::Value &value, BinaryStream *bs);
  void	serializeFloat(const Ultra::Value &value, BinaryStream *bs);
  void	serializeDouble(const Ultra::Value &value, BinaryStream *bs);
  void	serializeString(const Ultra::Value &value, BinaryStream *bs);
  void	serializeBool(const Ultra::Value &value, BinaryStream *bs);
  
  Ultra::Value	unserializeChar(BinaryStream *bs);
  Ultra::Value	unserializeUChar(BinaryStream *bs);
  Ultra::Value	unserializeShort(BinaryStream *bs);
  Ultra::Value	unserializeUShort(BinaryStream *bs);
  Ultra::Value	unserializeInt(BinaryStream *bs);
  Ultra::Value	unserializeUInt(BinaryStream *bs);
  Ultra::Value	unserializeLong(BinaryStream *bs);
  Ultra::Value	unserializeULong(BinaryStream *bs);
  Ultra::Value	unserializeFloat(BinaryStream *bs);
  Ultra::Value	unserializeDouble(BinaryStream *bs);
  Ultra::Value	unserializeString(BinaryStream *bs);
  Ultra::Value	unserializeBool(BinaryStream *bs);

};

#endif // __MESSAGE_HPP__
