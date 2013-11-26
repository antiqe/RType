#include <cstdio>
#include <iostream>

#include "FormatRoomInfo.hpp"

FormatRoomInfo::FormatRoomInfo()
{
}

FormatRoomInfo::~FormatRoomInfo()
{
}

std::string FormatRoomInfo::toString(std::string name, bool isPrivate, int playerIn, int playerMax)
{
  size_t	size = 1000;
  char		str[1000];
#ifdef _WIN32
  _snprintf(str, size, "  %-10s%-60s%-20d%-20d", ((isPrivate) ? "Yes" : "No"), name.c_str(), playerIn, playerMax);
#else
  _snprintf(str, size, "  %-10s%-60s%-20d%-20d", ((isPrivate) ? "Yes" : "No"), name.c_str(), playerIn, playerMax);
#endif
  return str;
}
