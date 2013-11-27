#include <iostream>

#include        "ASoundModule.hpp"

namespace Engine
{
  ASoundModule::ASoundModule()
    : AModule(60)
  {
    float percent1[3] = {0.2f,0.2f,0.8f};
    std::vector<float> first (percent1, percent1 + sizeof(percent1) / sizeof(float));
    float percent2[3] = {0.4f,0.6f,0.0f};
    std::vector<float> second (percent2, percent2 + sizeof(percent2) / sizeof(float));
    float percent3[3] = {0.2f,0.2f,0.6f};
    std::vector<float> third (percent3, percent3 + sizeof(percent3) / sizeof(float));
    float percent4[3] = {1.0f,1.0f,1.0f};
    std::vector<float> volume_sounds (percent4, percent4 + sizeof(percent4) / sizeof(float));
    this->_percent[0] = first;
    this->_percent[1] = second;
    this->_percent[2] = third;
    this->_percent[3] = volume_sounds;
  }

  ASoundModule::~ASoundModule(){}

  void		ASoundModule::addSound(const std::string &name, ISound *sound)

  {
    this->_sounds[name] = sound;
  }

  void		ASoundModule::_changeVolume()
  {
    std::list<std::pair<ISound *, int> >::iterator it;
    int	nbSoundType[3] = {0,0,0};
    int   percent;

    for (it = this->_playing.begin(); it != this->_playing.end(); ++it)
      nbSoundType[static_cast<int>(((*it).first)->getType())] += 1;
    if (nbSoundType[0] == 0 || nbSoundType[1] == 0)
      percent = 0;
    else if (nbSoundType[2] == 0)
      percent = 1;
    else
      percent = 2;
    int nb = 0;
    for (it = this->_playing.begin(); it != this->_playing.end(); ++it)
      {
	nb = nbSoundType[(((*it).first)->getType())];
	(*it).first->volume((((this->_percent[percent])[(((*it).first)->getType())]
			      * this->_percent[3][(((*it).first)->getType())] / 1.0f) / static_cast<float>(nb)));
      }
  }

  void		ASoundModule::_manageSounds(void)
  {
    int	nbSounds = this->_playing.size();

    if (nbSounds == 1)
      (this->_playing.front()).first->volume(this->_percent[3][this->_playing.front().first->getType()]);
    else
      this->_changeVolume();
  }

  void		ASoundModule::manageSounds(void)
  {
    std::list<std::pair<ISound *, int> >::iterator it;
    std::list<std::list<std::pair<ISound *, int> >::iterator> tmp;

    if (this->_playing.empty() == false)
      for (it = this->_playing.begin(); it != this->_playing.end(); ++it)
	{
	  if ((*it).first->isPlaying() == false && ((*it).second > 0 || (*it).second == -1))
	    {
	      if ((*it).second != -1)
		((*it).second)--;
	      (*it).first->play();
	    }
	  else if ((*it).second == 1)
	    tmp.push_front(it);
	}

    std::list<std::list<std::pair<ISound *, int> >::iterator>::iterator it_tmp;
    if (tmp.empty() == false)
      {
	for (it_tmp = tmp.begin(); it_tmp != tmp.end(); ++it_tmp)
	  this->_playing.erase(*it_tmp);
	_manageSounds();
      }
  }

  void		ASoundModule::playSound(const std::string &name)
  {
    std::map<std::string, ISound *>::iterator it;

    if ((it = this->_sounds.find(name)) == this->_sounds.end())
      return;

    std::pair<ISound *, int> tmp ((*it).second, ((*it).second)->getFrequence());
    this->_playing.push_back(tmp);
    this->_manageSounds();
    (*it).second->play();
  }

  void		ASoundModule::stopSound(const std::string &name)
  {
    std::list<std::pair<ISound *, int> >::iterator it;

    for (it = this->_playing.begin(); it != this->_playing.end(); ++it)
      if (((*it).first->getName()).compare(name) == 0)
	{
	  (*it).first->stop();
	  this->_playing.erase(it);
	}
  }

  void		ASoundModule::volumeSounds(float ds, ISound::type type)
  {
    this->_percent[3][static_cast<int>(type)] = ds;
  }

  void		ASoundModule::volumeSounds(float ds)
  {
    this->_percent[3][0] = ds;
    this->_percent[3][1] = ds;
    this->_percent[3][2] = ds;
  }

  std::string const&	ASoundModule::getID() const
  {
    return (AModule::SOUND);
  }
}
