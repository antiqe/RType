#ifndef _PLAYER_H_
# define _PLAYER_H_

#include <string>

#include "Widget.hpp"
#include "IImage.hpp"
#include "Vector2D.hpp"
#include "IRender.hpp"
#include "AGauge.hpp"
#include "Player.hpp"
#include "GameObjectViewer.hpp"
#include "GameObjectFactory.hpp"
#include "CheckBox.hpp"
#include "Label.hpp"
#include "Background.hpp"
#include "DataModule.hpp"
#include "IText.hpp"

class Player : public Engine::Widget
{
	enum Statistic
	{
		ARMOR = 0,
		POWER,
		SPEED,
		STAT_SIZE
	};

	Engine::CheckBox*			_ready;
	Engine::GameObjectViewer*	_shipViewer;
	Engine::Label*				_login;
	Engine::Background*			_iconStats[STAT_SIZE];
	Engine::AGauge*				_stats[STAT_SIZE];
	GameObjectFactory			_gameObjectFactory;
	DataModule*					_dataModule;

public:
	Player(std::string const &idPlayer);
	virtual ~Player();

	virtual	void	initialize();
	virtual void	update();
	virtual void	unload();
	virtual void	draw(Engine::IRender* render);

	bool	isReady() const;

	Engine::CheckBox*	getReadyButton();
};

#endif
