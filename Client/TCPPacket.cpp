#include <cstring>

#include "Core.hpp"
#include "TCPPacket.hpp"
#include "BinaryStream.hpp"
#include "Message.hpp"
#include "ScopeLock.hpp"

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

	//  std::cout << "this length:"<< this->_len << " length:" << length << std::endl;
	if (!bs.read<unsigned short>(this->_len) || this->_len != length)
	{
		//std::cout << "unpack false" << std::endl;
		return false;
	}
	if (!bs.read<unsigned char>(this->_srv))
	{
		//std::cout << "unpack false" << std::endl;
		return false;
	}
	if (!bs.read<unsigned short>(id))
	{
		//std::cout << "unpack false" << std::endl;
		return false;
	}
	//std::cout << "unpack true" << std::endl;
	Ultra::ScopeLock	lock(Engine::Core::getInstance()->access());
	this->_data = Engine::Core::messagefactory->create(id);
	if (this->_data)
		this->_data->unserialize(bs.getBuffer(), bs.getSize());
	else
		return false;
	return true;

}
