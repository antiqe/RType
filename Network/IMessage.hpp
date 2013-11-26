#ifndef __IMESSAGE_HH__
#define __IMESSAGE_HH__

class IMessage
{
public:
  virtual char *serialize(unsigned short &length) = 0;
  virtual unsigned short getID() const = 0;
  virtual void unserialize(char *data, unsigned int const length) = 0;
};

#endif