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
# include "GameObjectFactory.hpp"
# include "SFMLText.hpp"

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
	GameObjectFactory			_gameObjectFactory;

public:
	RoomState();
	~RoomState();

	void	initialize();
	void	update();
	void	unload();
	void	reset();
	void	reload();

	void	quitRoom();

	void	roomTalk();
	void	sendPlayerInfo();
};

#endif