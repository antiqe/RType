#ifndef __BINARYSTREAM_HPP__
#define __BINARYSTREAM_HPP__

#include <string>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>

#include <stdio.h>

class BinaryStream
{
private:

  char		*_begin;
  char		*_buffer;
  unsigned int  _size;
  unsigned int	_cwrite;

public:
 
  BinaryStream();
  BinaryStream(char *buffer, unsigned int const size);
  BinaryStream(BinaryStream const &s);
  BinaryStream &operator=(BinaryStream &s);

  template<typename T> bool read(T &d)
  {
    unsigned int d_size = sizeof(T);
    char *cur = reinterpret_cast<char *>(&d);
    char *end = reinterpret_cast<char *>(&d) + d_size;

    if (!this->_buffer && this->isReadable<T>())
      return (false);
    
    while (cur != end)
      {
	*cur = *(this->_buffer);
	++cur;
	/*if (cur != end)
	  ++this->_buffer;*/
	++this->_buffer;
      }

    this->_cwrite -= d_size;
    
    return (true);
  }
  
  template<typename T> bool write(T d)
  {
    unsigned int d_size = sizeof(T);
    char *cur = reinterpret_cast<char *>(&d);
    char *end = reinterpret_cast<char *>(&d) + d_size;
    
    if ((this->_buffer = reinterpret_cast<char *>(realloc(this->_buffer, sizeof(char) * (this->_cwrite + d_size))))== 0)
      return (false);
    
    this->_begin = this->_buffer;
    
    int i = 0;
    for (; cur != end; ++cur)
      {
	this->_buffer[i + this->_cwrite] = *cur;
	++i;
      }
    
    this->_cwrite += d_size;
    return (true);
  }
  
  template<typename T> bool operator<<(T data) { return (this->write<T>(data)); }
  template<typename T> bool operator>>(T &data) { return (this->read<T>(data)); }
  
  void clear();
  
  char *str() const;
  unsigned int size() const;

  bool isEmpty() const;

  
  template<typename T> bool isReadable()
  {
    return (this->_cwrite > sizeof(T) ? true : false);
  }

  char *getBuffer() const;
  unsigned int getSize() const;
  
private:
  
  void setBegin(char *begin);
  void setBuffer(char *buffer);
  void setSize(unsigned int const size);
  void setByteWrite(unsigned int const cwrite);
};

template <> bool BinaryStream::read<std::string>(std::string &);
template <> bool BinaryStream::write<std::string>(std::string);


#endif