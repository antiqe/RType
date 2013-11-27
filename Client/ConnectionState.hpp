#ifndef _CONNECTION_STATE_H_
# define _CONNECTION_STATE_H_

# include "IRender.hpp"
# include "DataModule.hpp"
# include "NetworkModule.hpp"
# include "Button.hpp"
# include "TextBox.hpp"
# include "Background.hpp"

class ConnectionState : public Engine::AState
{
private:
	DataModule*				_dataModule;
	NetworkModule*			_networkModule;
	Engine::Background*		_background;
	Engine::Button*			_connection;
	Engine::TextBox*		_login;
	Engine::TextBox*		_password;
	Engine::TextBox*		_ip;
	Engine::TextBox*		_port;
	Engine::Button*			_settings;
	Engine::Button*			_quit;
	Engine::Background*		_loading;

	static void	setInputText(Engine::TextBox* widget, size_t fontSize);

public:
	ConnectionState();
	~ConnectionState();

	void	initialize();
	void	update();
	void	unload();
	void	reset();
	void	reload();
	void	resize(size_t width, size_t height);

	void	connect();
	void	login();
	void	play();
	void	displayError(std::string const &error);
};

#endif
