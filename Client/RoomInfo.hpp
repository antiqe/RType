#ifndef _ROOMINFO_H_
# define _ROOMINFO_H_

#include <string>

class RoomInfo
{
  unsigned short _id;
  std::string	_name;
  bool		_isPrivate;
  int		_playerIn;
  int		_playerMax;

public:
  RoomInfo(unsigned short const id, const std::string &name, bool isPrivate, int playerIn, int playerMax);
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

  unsigned short getID() const;
  void			 setID(unsigned short const id);

};

#endif /* _ROOMPLAYER_H_ */
