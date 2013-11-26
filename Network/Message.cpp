#include <map>

#include "Message.hpp"

Message::Message(unsigned short const id)
  : _id(id)
{
  this->initMap();
}

Message::Message(Message const &msg)
  : Ultra::Attr(msg), _id(msg._id)
{
  this->initMap();
}

Message::~Message()
{
		
}

void Message::initMap()
{
  _ptrSerialize[Ultra::Value::CHAR] = &Message::serializeChar;
  _ptrSerialize[Ultra::Value::UCHAR] = &Message::serializeUChar;
  _ptrSerialize[Ultra::Value::SHORT] = &Message::serializeShort;
  _ptrSerialize[Ultra::Value::USHORT] = &Message::serializeUShort;
  _ptrSerialize[Ultra::Value::INT] = &Message::serializeInt;
  _ptrSerialize[Ultra::Value::UINT] = &Message::serializeUInt;
  _ptrSerialize[Ultra::Value::LONG] = &Message::serializeLong;
  _ptrSerialize[Ultra::Value::ULONG] = &Message::serializeULong;
  _ptrSerialize[Ultra::Value::FLOAT] = &Message::serializeFloat;
  _ptrSerialize[Ultra::Value::DOUBLE] = &Message::serializeDouble;
  _ptrSerialize[Ultra::Value::STRING] = &Message::serializeString;
  _ptrSerialize[Ultra::Value::BOOL] = &Message::serializeBool;
	
  _ptrUnserialize[Ultra::Value::CHAR] = &Message::unserializeChar;
  _ptrUnserialize[Ultra::Value::UCHAR] = &Message::unserializeUChar;
  _ptrUnserialize[Ultra::Value::SHORT] = &Message::unserializeShort;
  _ptrUnserialize[Ultra::Value::USHORT] = &Message::unserializeUShort;
  _ptrUnserialize[Ultra::Value::INT] = &Message::unserializeInt;
  _ptrUnserialize[Ultra::Value::UINT] = &Message::unserializeUInt;
  _ptrUnserialize[Ultra::Value::LONG] = &Message::unserializeLong;
  _ptrUnserialize[Ultra::Value::ULONG] = &Message::unserializeULong;
  _ptrUnserialize[Ultra::Value::FLOAT] = &Message::unserializeFloat;
  _ptrUnserialize[Ultra::Value::DOUBLE] = &Message::unserializeDouble;
  _ptrUnserialize[Ultra::Value::STRING] = &Message::unserializeString;
  _ptrUnserialize[Ultra::Value::BOOL] = &Message::unserializeBool;
}

Message &Message::operator=(Message const &msg)
{
  Ultra::Attr::operator=(msg);
  if (&msg != this)
    this->_id = msg._id;
  return (*this);
}

char	*Message::serialize(unsigned short &length)
{
  std::map<std::string, Ultra::Value>::iterator iter;
  BinaryStream	bs;

  bs.write<unsigned short>(this->_id);

  for (iter = _attr.begin(); iter != _attr.end(); ++iter)
    (this->*_ptrSerialize[iter->second.getType()])(Ultra::Value(iter->second), &bs);

  length = bs.size();
  return bs.str();
}

void	Message::unserialize(char *msg, const unsigned int length)
{
  std::map<std::string, Ultra::Value>::iterator iter = _attr.begin();
  BinaryStream	bs(msg, length);

  while (!bs.isEmpty() && iter != _attr.end())
    {
      iter->second = (this->*_ptrUnserialize[iter->second.getType()])(&bs);
      ++iter;
    }
}

void	Message::serializeChar(const Ultra::Value &value, BinaryStream *bs)
{
	*bs << value.as<char>();
}

void	Message::serializeUChar(const Ultra::Value &value, BinaryStream *bs)
{
	*bs << value.as<unsigned char>();
}

void	Message::serializeShort(const Ultra::Value &value, BinaryStream *bs)
{
	*bs << value.as<short>();
}

void	Message::serializeUShort(const Ultra::Value &value, BinaryStream *bs)
{
	*bs << value.as<unsigned short>();
}

void	Message::serializeInt(const Ultra::Value &value, BinaryStream *bs)
{
	*bs << value.as<int>();
}

void	Message::serializeUInt(const Ultra::Value &value, BinaryStream *bs)
{
	*bs << value.as<unsigned int>();
}

void	Message::serializeLong(const Ultra::Value &value, BinaryStream *bs)
{
	*bs << value.as<long>();
}

void	Message::serializeULong(const Ultra::Value &value, BinaryStream *bs)
{
	*bs << value.as<unsigned long>();
}

void	Message::serializeFloat(const Ultra::Value &value, BinaryStream *bs)
{
	*bs << value.as<float>();
}

void	Message::serializeDouble(const Ultra::Value &value, BinaryStream *bs)
{
	*bs << value.as<double>();
}

void	Message::serializeString(const Ultra::Value &value, BinaryStream *bs)
{
  *bs << value.as<std::string>();
}

void	Message::serializeBool(const Ultra::Value &value, BinaryStream *bs)
{
  *bs << value.as<bool>();
}

Ultra::Value	Message::unserializeChar(BinaryStream *bs)
{
	char value;

	*bs >> value;
	return (Ultra::Value(value));
}

Ultra::Value	Message::unserializeUChar(BinaryStream *bs)
{
	unsigned char value;

	*bs >> value;
	return (Ultra::Value(value));
}

Ultra::Value	Message::unserializeShort(BinaryStream *bs)
{
	short value;

	*bs >> value;
	return (Ultra::Value(value));
}

Ultra::Value	Message::unserializeUShort(BinaryStream *bs)
{
	unsigned short value;

	*bs >> value;
	return (Ultra::Value(value));
}

Ultra::Value	Message::unserializeInt(BinaryStream *bs)
{
	int value;

	*bs >> value;
	return (Ultra::Value(value));
}

Ultra::Value	Message::unserializeUInt(BinaryStream *bs)
{
	unsigned int value;

	*bs >> value;
	return (Ultra::Value(value));
}

Ultra::Value	Message::unserializeLong(BinaryStream *bs)
{
	long value;

	*bs >> value;
	return (Ultra::Value(value));
}

Ultra::Value	Message::unserializeULong(BinaryStream *bs)
{
	unsigned long value;

	*bs >> value;
	return (Ultra::Value(value));
}

Ultra::Value	Message::unserializeFloat(BinaryStream *bs)
{
  float value;
  
  *bs >> value;
  return (Ultra::Value(value));
}

Ultra::Value	Message::unserializeDouble(BinaryStream *bs)
{
  double value;
  
  *bs >> value;
  return (Ultra::Value(value));
}

Ultra::Value	Message::unserializeString(BinaryStream *bs)
{
  std::string value;
  
  *bs >> value;
  return (Ultra::Value(value));
}

Ultra::Value	Message::unserializeBool(BinaryStream *bs)
{
  bool value;
  
  *bs >> value;
  return (Ultra::Value(value));
}

unsigned short	Message::getID() const
{
  return (this->_id);
}

void Message::setID(unsigned short id)
{
  this->_id = id;
}

bool Message::operator==(Message const &msg)
{
  return (this->_id == msg.getID());
}

Message *Message::clone() const
{
  return (new Message(*this));
}
