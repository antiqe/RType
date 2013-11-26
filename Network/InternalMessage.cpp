#include "InternalMessage.hh"

InternalMessage::InternalMessage(APacket *packet, int const from)
  : _fromTCP(from), _packet(packet), _proto(ISocket::TCP)
{
}

InternalMessage::InternalMessage(APacket *packet, struct sockaddr_in const &from)
  : _fromUDP(from), _packet(packet), _proto(ISocket::UDP)
{
}

int InternalMessage::getProto() const
{
  return (this->_proto);
}

int InternalMessage::getFromTCP() const
{
  return (this->_fromTCP);
}

struct sockaddr_in const &InternalMessage::getFromUDP() const
{
  return (this->_fromUDP);
}

void InternalMessage::setFromTCP(int const from)
{
  this->_fromTCP = from;
}

void InternalMessage::setFromUDP(struct sockaddr_in const &from)
{
  this->_fromUDP = from;
}

void InternalMessage::addReceiver(int const to)
{
  this->_toTCP.push_back(to);
}

void InternalMessage::addReceiver(struct sockaddr_in const &to)
{
  this->_toUDP.push_back(to);
}

std::list<int> const &InternalMessage::getReceiversTCP() const
{
  return (this->_toTCP);
}

std::list<struct sockaddr_in> const &InternalMessage::getReceiversUDP() const
{
  return (this->_toUDP);
}

APacket *InternalMessage::getPacket()
{
  return (this->_packet);
}
