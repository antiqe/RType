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

class GameState : public Engine::AState
{
private:
	DataModule*			_dataModule;
	Engine::HParallax*	_background;
	Engine::HParallax*	_terre;
	Engine::LogicTree*	_logicTree;
public:
	GameState();
	~GameState();

	void	initialize();
	void	update();
	void	unload();
	void	reset();
	void	reload();
};

#endif