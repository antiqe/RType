#ifndef __TCPPACKET_H__
#define __TCPPACKET_H__

#include "APacket.hpp"

class TCPPacket : public APacket
{
public:
  TCPPacket(IMessage *data = 0, unsigned char const srv = 0);
  virtual char *pack(unsigned short &length) const;
  virtual bool unpack(char *data, unsigned short const length);
};

#endif