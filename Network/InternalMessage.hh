#ifndef __INTERNALMESSAGE_HH__
#define __INTERNALMESSAGE_HH__

#include <list>
#include <utility>

#include "APacket.hpp"
#include "ASocket.hpp"

class InternalMessage
{
private:
  int _fromTCP;
  struct sockaddr_in _fromUDP;
  std::list<int> _toTCP;
  std::list<struct sockaddr_in> _toUDP;
  APacket *_packet;
  ISocket::Protocol _proto;
public:
  InternalMessage(APacket *packet, int const from);
  InternalMessage(APacket *packet, struct sockaddr_in const &from);
  APacket *getPacket();
  int getProto() const;
  int getFromTCP() const;
  struct sockaddr_in const &getFromUDP() const;
  void setFromTCP(int const from);
  void setFromUDP(struct sockaddr_in const &from);
  void addReceiver(int const to);
  void addReceiver(struct sockaddr_in const &to);
  std::list<int> const &getReceiversTCP() const;
  std::list<struct sockaddr_in> const &getReceiversUDP() const;
};

#endif
