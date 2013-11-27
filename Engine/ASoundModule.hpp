#ifndef _ASOUNDMODULE_H_
# define _ASOUNDMODULE_H_

#include <map>
#include <list>
#include <utility>
#include <string>
#include <vector>

#include "AModule.hpp"
#include "ISound.hpp"

namespace Engine
{
  class ASoundModule : public AModule
  {
    std::map<std::string, ISound *>        _sounds;
    std::list<std::pair<ISound *, int> >        _playing;
    std::map<int, std::vector<float> > _percent;

  public:
    ASoundModule();
    virtual	~ASoundModule();

    std::string const&	getID() const;

    void		addSound(const std::string &name, ISound *sound);
    void		playSound(const std::string &name);
    void		stopSound(const std::string &name);
    void		manageSounds(void);
    void		volumeSounds(float ds, ISound::type type);
    void		volumeSounds(float ds);

  private:
    void		_manageSounds(void);
    void		_changeVolume();
  };
}

#endif
