//
// Aggregator.cpp for  in /home/boisbr_t//project/rtype/Server
// 
// Made by titouan boisbras
// Login   <boisbr_t@epitech.net>
// 
// Started on  Wed Nov  6 13:26:11 2013 titouan boisbras
// Last update Tue Nov 19 17:00:22 2013 titouan boisbras
//

#include <iostream>
#include <utility>
#include <string.h>
#include "Aggregator.hpp"

Aggregator::Aggregator()
  : _size(0)
{
  this->_tmp = new char[maxSize];
}

Aggregator::~Aggregator()
{
  delete []_tmp;
}

void	Aggregator::integrity(int sizeRead, char *buffer, APacket *packet)
{
  int	packLen = 0;
  int	count = 0;
  unsigned int check = 0;

  if (this->_size > 0)
    {
      if ((this->_size + sizeRead) > maxSize)
	this->_size = 0;
      memcpy(this->_tmp, this->_msg, this->_size);
      memcpy(this->_tmp + this->_size, buffer, sizeRead);
      sizeRead += this->_size;
    }
  else
    memcpy(this->_tmp, buffer, sizeRead);
  if (packet->unpack(this->_tmp, sizeRead) == false)
    {
      packLen = packet->getLength();
      while (sizeRead >= packLen)
	{
	  if (packet->unpack(this->_tmp + count, packLen) == true)
	    {
	      this->_buffer.push(std::pair<char *, size_t>(this->_tmp + count, packLen));
	      sizeRead -= packLen;
	      count += packLen;
	    }
	  packLen = packet->getLength();
	  check++;
	  if (check >= maxSize)
	    sizeRead = 0;
	}
      if (sizeRead > 0 && sizeRead < packLen)
	{
	  memcpy(this->_msg, this->_tmp + count, sizeRead);
	  this->_size = sizeRead;
	  return ;
	}
      else
	{
	  this->_size = 0;
	  return ;
	}
    }
  this->_buffer.push(std::pair<char *, size_t>(buffer, sizeRead));
}

std::pair<char *, size_t>  Aggregator::getMsgFront() const
{
  return this->_buffer.front();
}

std::pair<char *, size_t> Aggregator::getMsgBack() const
{
  return this->_buffer.back();
}

void	Aggregator::popMsg()
{
  this->_buffer.pop();
}

bool	Aggregator::isEmpty()
{
  return _buffer.empty();
}
