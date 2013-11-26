#ifndef _FORMATROOMINFO_H_
# define _FORMATROOMINFO_H_

#include <string>

class FormatRoomInfo
{
public:
  FormatRoomInfo();
  ~FormatRoomInfo();
  static std::string toString(std::string name, bool isPrivate, int playerIn, int playerMax);
};

#endif /* _FORMATROOMPLAYER_H_ */
