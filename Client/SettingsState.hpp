#ifndef _SETTINGS_STATE_H_
# define _SETTINGS_STATE_H_

# include "IRender.hpp"
# include "DataModule.hpp"
# include "Button.hpp"
# include "TextBox.hpp"
# include "Background.hpp"
# include "SFMLAnimation.hpp"
# include "ASlider.hpp"
# include "CheckBox.hpp"
# include "KeyBox.hpp"

class SettingsState : public Engine::AState
{
private:
	DataModule*				_dataModule;
	Engine::Background*		_background;
	Engine::KeyBox*			_moveUp;
	Engine::KeyBox*			_moveDown;
	Engine::KeyBox*			_moveLeft;
	Engine::KeyBox*			_moveRight;
	Engine::KeyBox*			_shoot;
	Engine::ASlider*		_ambient;
	Engine::ASlider*		_effect;
	Engine::ASlider*		_global;
	Engine::ASlider*		_resolution;
	Engine::CheckBox*		_fullscreen;
	Engine::Button*			_quit;
	Engine::Button*			_settings;
	Engine::Button*			_back;
	Engine::Background*		_loading;

public:
	SettingsState();
	~SettingsState();

	void	initialize();
	void	update();
	void	unload();
	void	reset();
	void	reload();
};

#endif