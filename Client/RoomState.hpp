#ifndef _ROOM_STATE_H_
# define _ROOM_STATE_H_

# include "IRender.hpp"
# include "DataModule.hpp"
# include "Button.hpp"
# include "TextBox.hpp"
# include "Background.hpp"
# include "SFMLAnimation.hpp"
# include "NetworkModule.hpp"
# include "AGauge.hpp"
# include "ListBox.hpp"
# include "SFMLText.hpp"
# include "Player.hpp"

class RoomState : public Engine::AState
{
	static const unsigned int nbrPlayer = 4;

	DataModule*					_dataModule;
	Engine::Background*			_background;
	Engine::Button*				_go;
	Engine::ListBox<>*			_chatBox;
	Engine::TextBox*			_msg;
	Engine::Button*				_send;
	Engine::Button*				_quit;
	Engine::Button*				_settings;
	Engine::Button*				_back;
	Engine::Background*			_loading;
	NetworkModule*				_networkModule;
	Player*						_players[nbrPlayer];
	Engine::CheckBox*			_ready[nbrPlayer];

public:
	RoomState();
	~RoomState();

	void	initialize();
	void	update();
	void	unload();
	void	reset();
	void	reload();
	void	resize(size_t width, size_t height);

	void	quitRoom();

	void	roomTalk();
	void	sendPlayerInfo();
	void	sendStartRoom();
};

#endif