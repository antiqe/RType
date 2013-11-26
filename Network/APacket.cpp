#include "APacket.hpp"

APacket::APacket(IMessage *data, unsigned char const)
  : _data(data), _len(0), _srv(0)
{
}

void APacket::setData(IMessage *data)
{
  this->_data = data;
}

IMessage *APacket::getData() const
{
  return (this->_data);
}

unsigned short APacket::getLength() const
{
  return (this->_len);
}

unsigned char APacket::getService() const
{
  return (this->_srv);
}

unsigned short APacket::calcSum(char *buffer, unsigned short const length) const
{
  unsigned short x;

  x = 0;
  for (unsigned short i = 0; i < length; ++i)
    x ^= buffer[i];
  return (x);
}
