#include <cstring>

#include "Core.hh"
#include "TCPPacket.hh"
#include "BinaryStream.hpp"
#include "Message.hpp"

TCPPacket::TCPPacket(IMessage *data, unsigned char const srv)
  : APacket(data, 0)
{
  this->_srv = srv;
}


char *TCPPacket::pack(unsigned short &length) const
{
  char *dbuffer;
  char *hbuffer;
  BinaryStream b;
  unsigned short dsize;
  unsigned short hsize;

  dbuffer = this->_data->serialize(dsize);

  length = dsize + sizeof(this->_len) + sizeof(this->_srv);

  b << length;
  b << this->_srv;
  hsize = b.size();
  hbuffer = b.str();

  hbuffer = (char *)realloc(hbuffer, sizeof(char) * length);
  memcpy(&hbuffer[hsize], dbuffer, dsize);

  //std::cout << "Sum = " << this->calcSum(hbuffer, length) << std::endl;

  free(dbuffer);
  return (hbuffer);
}

bool TCPPacket::unpack(char *data, unsigned short const length)
{
  unsigned short id;
  BinaryStream bs(data, length);

  if (!bs.read<unsigned short>(this->_len) || this->_len != length)
      return false;
  if (!bs.read<unsigned char>(this->_srv))
      return false;
  if (!bs.read<unsigned short>(id))
      return false;

  this->_data = Core::mfactory->create(id);
  if (this->_data)
    this->_data->unserialize(bs.getBuffer(), bs.getSize());
  else
    return false;
  return true;

}
