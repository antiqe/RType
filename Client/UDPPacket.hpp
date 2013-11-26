#ifndef __UDPPACKET_H__
#define __UDPPACKET_H__

#include "APacket.hpp"

class UDPPacket : public APacket
{
private:
	unsigned short _id;
	unsigned short _clock;
public:
	UDPPacket();
	UDPPacket(IMessage *data, unsigned char const srv, unsigned short const id, unsigned short const clock);
	unsigned short getClock() const;
	unsigned short getID() const;
	void setID(unsigned short const id);
	void setClock(unsigned short const clock);
	virtual char *pack(unsigned short &length) const;
	virtual bool unpack(char *data, unsigned short const length);
};

#endif