#include <iostream>
#include <string.h>

#include "BinaryStream.hpp"

BinaryStream::BinaryStream()
  : _begin(0), _buffer(0), _size(0), _cwrite(0)
{ }

BinaryStream::BinaryStream(char *buffer, unsigned int const size)
  : _begin(buffer), _buffer(buffer), _size(size), _cwrite(size)
{ }

BinaryStream::BinaryStream(BinaryStream const &s)
{
  _buffer = s.getBuffer();
  _size = s.getSize();
  _begin = s.str();
  _cwrite = s.size();
}

BinaryStream &BinaryStream::operator=(BinaryStream &s)
{
  this->_buffer = s.getBuffer();
  this->_size = s.getSize();
  this->_begin = s.str();
  this->_cwrite = s.size();
  return (s);
}

char *BinaryStream::getBuffer() const
{
  return (this->_buffer);
}

unsigned int BinaryStream::getSize() const
{
  return (this->_size);
}

void BinaryStream::setSize(unsigned int const size)
{
  this->_size = size;
}

void BinaryStream::setBegin(char *begin)
{
  this->_begin = begin;
}

void BinaryStream::setBuffer(char *buffer)
{
  this->_buffer = buffer;
}

void BinaryStream::setByteWrite(unsigned int const cwrite)
{
  this->_cwrite = cwrite;
}

void BinaryStream::clear()
{
  this->_size = 0;
  this->_buffer = 0;
  this->_begin = 0;
  this->_cwrite = 0;
}

template<>
bool BinaryStream::read<std::string>(std::string &d)
{
  if (!this->_buffer)
    return (false);
  unsigned int d_size = 0;
  read(d_size);

  d.resize(d_size);
  std::copy(this->_buffer, this->_buffer + d_size, d.begin());
  this->_buffer += d_size;

  this->_cwrite -= d_size;

  return (true);
}

template<>
bool BinaryStream::write<std::string>(std::string d)
{
  unsigned int d_size = d.size();

  if (!write(d_size))
    return (false);

  if ((this->_buffer = reinterpret_cast<char *>(realloc(this->_buffer, sizeof(char) * (this->_cwrite + d_size)))) == 0)
    return (false);

  this->_begin = this->_buffer;

#ifdef _WIN32
  #pragma warning(disable : 4996)
#endif
  d.copy(&this->_buffer[this->_cwrite], d_size);

  this->_cwrite += d_size;
  return (true);
}

bool BinaryStream::isEmpty() const
{
  return (this->_cwrite == 0 ? true : false);
}

char *BinaryStream::str() const
{
  return (this->_begin);
}

unsigned int BinaryStream::size() const
{
  return (this->_cwrite);
}
