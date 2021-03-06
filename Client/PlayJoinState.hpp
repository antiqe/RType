#ifndef _PLAY_JOIN_STATE_H_
# define _PLAY_JOIN_STATE_H_

# include "IRender.hpp"
# include "DataModule.hpp"
# include "Button.hpp"
# include "RoomInfo.hpp"
# include "ListBox.hpp"
# include "Background.hpp"
# include "NetworkModule.hpp"

class PlayJoinState : public Engine::AState
{
private:
	DataModule*				_dataModule;
	Engine::Background*		_background;
	Engine::ListBox<RoomInfo *>*		_list;
	Engine::Button*			_select;
	Engine::Button*			_refresh;
	Engine::Button*			_quit;
	Engine::Button*			_settings;
	Engine::Button*			_back;
	Engine::Background*		_loading;
	NetworkModule*			_networkModule;

public:
	PlayJoinState();
	~PlayJoinState();

	void	initialize();
	void	update();
	void	unload();
	void	reset();
	void	reload();
	void	resize(size_t width, size_t height);

	void	roomListRequest();
	void    refresh();
	void	selectServer();

	void	goToRoom();
};

#endif