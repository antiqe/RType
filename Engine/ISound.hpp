#ifndef __ISOUND_H__
# define __ISOUND_H__

#include        <string>

namespace Engine
{
  class ISound
  {
  public:

    enum type
      {
	AMBIANCE = 0,
	EFFECT = 1,
	IMPORTANT = 2
      };

    virtual ~ISound(){}
    virtual void       	play(void) = 0;
    virtual void          stop(void) const = 0;
    virtual void          pause(void) = 0;
    virtual bool          isPlaying(void) = 0;
    virtual void          volume(float ds) = 0;
    virtual void          repeat(void) = 0;
    virtual void		reset(void) = 0;
    virtual ISound::type	        getType(void) const = 0;
    virtual int		getFrequence(void) const = 0;
    virtual const std::string &getName(void) const = 0;

  };
}

#endif
