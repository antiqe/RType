#ifndef _STATEMODULE_H_
# define _STATEMODULE_H_

#include <stack>
#include <map>
#include <string>

#include "AStateModule.hpp"

class StateModule : public Engine::AStateModule
{
public:
	StateModule();
	~StateModule();

	void	initialize();
	void	update();
	void	unload();
};

#endif