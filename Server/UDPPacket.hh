#ifndef __UDPPACKET_HH__
#define __UDPPACKET_HH__

#include "APacket.hpp"

class UDPPacket : public APacket
{
private:
  unsigned int _id;
  unsigned short _clock;
public:
  UDPPacket();
  UDPPacket(IMessage *data, unsigned char const srv, unsigned short const id,
	    unsigned short const clock);
  unsigned short getClock() const;
  unsigned short getID() const;
  void setID(unsigned short const id);
  void setClock(unsigned short const clock);
  virtual char *pack(unsigned short &length) const;
  virtual bool unpack(char *data, unsigned short const length);
  static void unpackID(unsigned int const packid, unsigned short &room, unsigned short &id);
  static unsigned int packID(unsigned short const room, unsigned short const id);
};

#endif