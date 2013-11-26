#ifndef _STATE_H_
# define _STATE_H_

#include <string>

class State
{
private:
	State();
public:
	static std::string const	CONNECTION;
	static std::string const	MENU;
	static std::string const	PAUSE;
	static std::string const	PLAY;
	static std::string const	PLAY_CREATE;
	static std::string const	PLAY_JOIN;
	static std::string const	RANKING;
	static std::string const	ROOM;
	static std::string const	SETTINGS;
	static std::string const	GAME;
};

#endif