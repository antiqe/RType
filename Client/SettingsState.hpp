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

class SettingsState : public Engine::AState
{
private:
	DataModule*				_dataModule;
	Engine::Background*		_background;
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