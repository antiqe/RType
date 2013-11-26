#ifndef __IPACKET_H__
#define __IPACKET_H__

class IPacket
{
public:
  virtual char *pack(unsigned short &length) const = 0;
  virtual bool unpack(char *data, unsigned short const len) = 0;
};

#endif