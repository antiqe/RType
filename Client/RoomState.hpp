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
# include "CheckBox.hpp"
# include "GameObjectViewer.hpp"

class RoomState : public Engine::AState
{
private:
	enum Statistic
	{
		ARMOR = 0,
		POWER,
		SPEED,
		STAT_SIZE
	};

	static unsigned int nbrPlayer;

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
	Engine::CheckBox*			_ready[4];
	SFMLImage*					_iconStats[STAT_SIZE];
	Engine::AGauge*				_stats[STAT_SIZE];
	Engine::GameObjectViewer*	_shipViewer[4];
	NetworkModule*				_networkModule;

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
};

#endif