#ifndef _RENDERMODULE_H_
# define _RENDERMODULE_H_

#include "ARenderModule.hpp"
#include "IRender.hpp"
#include "DataModule.hpp"
#include "StateModule.hpp"
#include "Event.hpp"

class RenderModule : public Engine::ARenderModule
{
private:
	StateModule*		_stateModule;
	DataModule*			_dataModule;	
public:
	RenderModule();
	~RenderModule();

	void	initialize();
	void	update();
	void	unload();
	void	draw();
};

#endif