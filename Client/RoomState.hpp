#ifndef _ROOM_STATE_H_
# define _ROOM_STATE_H_

# include "IRender.hpp"
# include "DataModule.hpp"
# include "Button.hpp"
# include "TextBox.hpp"
# include "Background.hpp"

class RoomState : public Engine::AState
{
private:
	DataModule*				_dataModule;
	Engine::Background*		_background;
	Engine::Button*			_create;
	Engine::Button*			_join;
	Engine::Button*			_quit;
	Engine::Button*			_settings;
	Engine::Button*			_back;
	Engine::Background*		_loading;

public:
	RoomState();
	~RoomState();

	void	initialize();
	void	update();
	void	unload();
	void	reset();
	void	reload();
};

#endif