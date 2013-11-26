#ifndef __APACKET_H__
#define __APACKET_H__

#include "IPacket.hpp"
#include "IMessage.hpp"

class APacket : public IPacket
{
protected:
  IMessage *_data;
  unsigned short _sum;
  unsigned short _len;
  unsigned char _srv;
public:
  APacket(IMessage *data, unsigned char const srv);
  IMessage *getData() const;
  void setData(IMessage *data);
  unsigned short getLength() const;
  unsigned char getService() const;
  unsigned short getSum() const;
protected:
  unsigned short calcSum(char *buffer, unsigned short const length) const;
};

#endif