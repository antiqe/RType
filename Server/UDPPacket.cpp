#include <cstring>

#include "Core.hh"
#include "UDPPacket.hh"
#include "BinaryStream.hpp"
#include "Message.hpp"

UDPPacket::UDPPacket()
  : APacket(0, 0), _id(0), _clock(0)
{
  this->_srv = (unsigned char)0;
}

UDPPacket::UDPPacket(IMessage *data, unsigned char const srv,
		     unsigned short const id, unsigned short const clock)
  : APacket(data, 0), _id(id), _clock(clock)
{
  this->_srv = srv;
}

unsigned short UDPPacket::getClock() const
{
  return (this->_clock);
}

unsigned short UDPPacket::getID() const
{
  return (this->_id);
}

void UDPPacket::setID(unsigned short const id)
{
  this->_id = id;
}

void UDPPacket::setClock(unsigned short const clock)
{
  this->_clock = clock;
}

char *UDPPacket::pack(unsigned short &length) const
{
  char *dbuffer;
  char *hbuffer;
  BinaryStream b;
  unsigned short dsize;
  unsigned short hsize;

  dbuffer = this->_data->serialize(dsize);

  length = dsize + sizeof(this->_len) + 
    sizeof(this->_id) + sizeof(this->_clock) + sizeof(this->_srv);

  b << length;
  b << this->_srv;
  b << this->_id;
  b << this->_clock;
  hsize = b.size();
  hbuffer = b.str();

  hbuffer = (char *)realloc(hbuffer, sizeof(char) * length);
  memcpy(&hbuffer[hsize], dbuffer, dsize);
  
  free(dbuffer);
  return (hbuffer);  
}

bool UDPPacket::unpack(char *data, unsigned short const length)
{
  unsigned short id;
  BinaryStream bs(data, length);

  if (!bs.read<unsigned short>(this->_len) || this->_len != length)
    return false;
  if (!bs.read<unsigned char>(this->_srv))
    return false;
  if (!bs.read<unsigned int>(this->_id))
    return false;
  if (!bs.read<unsigned short>(this->_clock))
    return false;
  if (!bs.read<unsigned short>(id))
    return false;

  this->_data = Core::mfactory->create(id);
  if (this->_data)
    {
      this->_data->unserialize(bs.getBuffer(), bs.getSize());
      return true;
    }
  return false;
}

unsigned int UDPPacket::packID(unsigned short const room, unsigned short const id)
{
	return (room << 8 | id);
}

void UDPPacket::unpackID(unsigned int const packid, unsigned short &room, unsigned short &id)
{
	id = packid & 0xFFFF0000;
	room = packid & 0x0000FFFF;
}