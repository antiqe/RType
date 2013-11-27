#ifndef _GAMESTATE_H_
# define _GAMESTATE_H_

#include "IRender.hpp"
#include "DataModule.hpp"
#include "Button.hpp"
#include "TextBox.hpp"
#include "Background.hpp"
#include "CheckBox.hpp"
#include "ASlider.hpp"
#include "HParallax.hpp"
#include "LogicTree.hpp"
#include "ListBox.hpp"
#include "NetworkEvent.hpp"
#include "KeyboardEvent.hpp"

class GameState : public Engine::AState
{
private:
	DataModule*								_dataModule;
	Engine::HParallax*						_background;
	Engine::HParallax*						_terre;
	Engine::LogicTree*						_logicTree;
	std::map<int, bool>						_vectorMap;
	std::map<int, Ultra::Vector2D<float> >	_keyMap;
public:
	GameState();
	~GameState();

	void	initialize();
	void	update();
	void	unload();
	void	reset();
	void	reload();
	void	resize(size_t width, size_t height);

	void	maj(Engine::NetworkEvent* event);

	void	enableAction(Engine::KeyboardEvent* event);
	void	disableAction(Engine::KeyboardEvent* event);

	void	move();
};

#endif