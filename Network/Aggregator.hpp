//
// Aggregator.hpp for  in /home/boisbr_t//project/rtype/Server
// 
// Made by titouan boisbras
// Login   <boisbr_t@epitech.net>
// 
// Started on  Wed Nov  6 13:26:22 2013 titouan boisbras
// Last update Tue Nov 19 15:42:09 2013 titouan boisbras
//

#ifndef __AGGREGATOR_HPP__
#define __AGGREGATOR_HPP__

#include <queue>
#include <string>
#include "APacket.hpp"

const unsigned int maxSize = 2048;

class Aggregator
{
  char			_msg[maxSize];
  char			*_tmp;
  unsigned int		_size;
  std::queue<std::pair<char*, size_t> >	_buffer;

public:
  Aggregator();
  ~Aggregator();
  void	integrity(int size, char *buffer, APacket *packet);
  std::pair<char *, size_t>	getMsgFront() const;
  std::pair<char *, size_t>	getMsgBack() const;
  void	popMsg();
  bool	isEmpty();
};

#endif
