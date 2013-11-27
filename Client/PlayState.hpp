#ifndef _PLAY_STATE_H_
# define _PLAY_STATE_H_

# include "IRender.hpp"
# include "DataModule.hpp"
# include "Button.hpp"
# include "TextBox.hpp"
# include "Background.hpp"
# include "SFMLAnimation.hpp"

class PlayState : public Engine::AState
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
	PlayState();
	~PlayState();

	void	initialize();
	void	update();
	void	unload();
	void	reset();
	void	reload();
	void	resize(size_t width, size_t height);
};

#endif