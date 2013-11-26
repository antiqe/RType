#ifndef _PLAY_CREATE_STATE_H_
# define _PLAY_CREATE_STATE_H_

# include "IRender.hpp"
# include "DataModule.hpp"
# include "Button.hpp"
# include "TextBox.hpp"
# include "Background.hpp"
# include "NetworkModule.hpp"
# include "CheckBox.hpp"

class PlayCreateState : public Engine::AState
{
private:
	DataModule*			_dataModule;
	Engine::Background*	_background;
	Engine::TextBox*	_name;
	Engine::CheckBox*		_private;
	Engine::TextBox*	_password;
	Engine::Button*		_ok;
	Engine::Button*		_quit;
	Engine::Button*		_settings;
	Engine::Button*		_back;
	Engine::Background*	_loading;
	NetworkModule*		_networkModule;

public:
	PlayCreateState();
	~PlayCreateState();

	void	initialize();
	void	update();
	void	unload();
	void	reset();
	void	reload();

	void	createRoom();
	void	goToRoom();
	void	displayError(std::string const &msg);
};

#endif