#include <cstring>

#include "Core.hpp"
#include "UDPPacket.hpp"
#include "BinaryStream.hpp"
#include "Message.hpp"
#include "ScopeLock.hpp"

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
	if (!bs.read<unsigned short>(this->_id))
		return false;
	if (!bs.read<unsigned short>(this->_clock))
		return false;
	if (!bs.read<unsigned short>(id))
		return false;
	Ultra::ScopeLock	lock(Engine::Core::getInstance()->access());
	this->_data = Engine::Core::messagefactory->create(id);
	if (this->_data)
	{
		this->_data->unserialize(bs.getBuffer(), bs.getSize());
		return true;
	}
	return false;
}
