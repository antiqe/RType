#ifndef _ROOMINFO_H_
# define _ROOMINFO_H_

#include <string>

class RoomInfo
{
  std::string	_name;
  bool		_isPrivate;
  int		_playerIn;
  int		_playerMax;

public:
  RoomInfo(const std::string &name, bool isPrivate, int playerIn, int playerMax);
  ~RoomInfo();
  std::string toString();

  std::string	getName() const;
  void		setName(const std::string &name);

  bool		isPrivate() const;
  void		setIsPrivate(bool isPrivate);

  int		getPlayerIn() const;
  void		setPlayerIn(int playerIn);

  int		getPlayerMax() const;
  void		setPlayerMax(int playerMax);

};

#endif /* _ROOMPLAYER_H_ */
