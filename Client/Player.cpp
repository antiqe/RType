#include "Player.hpp"
#include "SFMLImage.hpp"
#include "SFMLText.hpp"
#include "HGauge.hpp"
#include "Core.hpp"

#include "AArmorComponent.hpp"
#include "ASpeedComponent.hpp"

//
// CTOR / DTOR
//

Player::Player(std::string const &idPlayer)
	: Engine::Widget("player" + idPlayer), 
	_ready(new Engine::CheckBox("ready", SFMLImage::CHECKBOX_CHECKED_NORMAL_READY, SFMLImage::CHECKBOX_CHECKED_CLICKED_READY,
	SFMLImage::CHECKBOX_CHECKED_HOVER_READY, SFMLImage::CHECKBOX_UNCHECKED_NORMAL_READY, SFMLImage::CHECKBOX_UNCHECKED_CLICKED_READY,
	SFMLImage::CHECKBOX_UNCHECKED_HOVER_READY)),
	_shipViewer(new Engine::GameObjectViewer("viewer", SFMLImage::BUTTON_NEXT, SFMLImage::BUTTON_CLICKED_NEXT, 
	SFMLImage::BUTTON_HOVER_NEXT, SFMLImage::BUTTON_PREV, SFMLImage::BUTTON_CLICKED_PREV, SFMLImage::BUTTON_HOVER_PREV)),
	_login(new Engine::Label("login", SFMLText::TEXTBOX, "???"))
{
	this->_shipViewer->push(Engine::GameObject::STARSHIP1, this->_gameObjectFactory.create(Engine::GameObject::STARSHIP1));
	this->_shipViewer->push(Engine::GameObject::STARSHIP2, this->_gameObjectFactory.create(Engine::GameObject::STARSHIP2));
	this->_shipViewer->push(Engine::GameObject::STARSHIP3, this->_gameObjectFactory.create(Engine::GameObject::STARSHIP3));
	this->_shipViewer->push(Engine::GameObject::STARSHIP4, this->_gameObjectFactory.create(Engine::GameObject::STARSHIP4));
	this->_iconStats[Player::ARMOR] = new Engine::Background("armor", SFMLImage::ARMOR);
	this->_iconStats[Player::POWER] = new Engine::Background("power", SFMLImage::POWER);
	this->_iconStats[Player::SPEED] = new Engine::Background("speed", SFMLImage::SPEED);
	this->_stats[Player::ARMOR] = new Engine::HGauge("armor", SFMLImage::GAUGE_BACKGROUND, SFMLImage::GAUGE_FILLED, 0);
	this->_stats[Player::POWER] = new Engine::HGauge("power", SFMLImage::GAUGE_BACKGROUND, SFMLImage::GAUGE_FILLED, 0);
	this->_stats[Player::SPEED] = new Engine::HGauge("speed", SFMLImage::GAUGE_BACKGROUND, SFMLImage::GAUGE_FILLED, 0);
}

Player::~Player()
{
}

//
// LIFE-CYCLE
//

void	Player::initialize()
{
	this->addChild(this->_ready);
	this->addChild(this->_shipViewer);
	this->addChild(this->_login);
	for (int i = 0 ; i < Player::STAT_SIZE ; ++i)
	{
		this->addChild(this->_iconStats[i]);
		this->addChild(this->_stats[i]);
	}
	if ((this->_dataModule = dynamic_cast<DataModule*>(Engine::Core::getInstance()->getModule(Engine::AModule::DATA))))
	{
		size_t	width = this->_dataModule->getAttr<size_t>("winWidth");
		size_t	height = this->_dataModule->getAttr<size_t>("winHeight");

		Widget::initialize();
		this->_ready->setSize(width * 6 / 100, height * 5 / 100);
		this->_ready->setPosition(width * 14 / 100, height * 22 / 100);
		this->_shipViewer->setSize(width * 9 / 100, height * 8 / 100);
		this->_shipViewer->setPosition(width * 10 / 100, height * 5 / 100);
		for (int i = 0 ; i < Player::STAT_SIZE ; ++i)
		{
			this->_iconStats[i]->setSize(width * 2 / 100, width * 2 / 100);
			this->_iconStats[i]->setPosition(0, (height * 23 / 100) - (i * (width * 2 / 100)));
			this->_stats[i]->setSize(width * 8 / 100, width * 2 / 100);
			this->_stats[i]->setPosition((int)((float)(width) * 2.25 / 100), (height * 23 / 100) - (i * (width * 2 / 100)));
		}
		this->_login->setTextSize((size_t)((float)(width * 2 / 100)));
		this->_login->setTextPosition(0, 5);
		this->_login->setTextColor(Ultra::Color(138, 212, 241, 255));
		this->_login->setTextStyle(0);
	}
}

void	Player::update()
{
	Widget::update();
	const Engine::GameObject* obj = this->_shipViewer->getFocusGameObject();
	Engine::AArmorComponent* armor = dynamic_cast<Engine::AArmorComponent*>(obj->getComponent(Engine::AComponent::ARMOR));
	Engine::ASpeedComponent* speed = dynamic_cast<Engine::ASpeedComponent*>(obj->getComponent(Engine::AComponent::SPEED));
	this->_stats[Player::POWER]->setPercent(50);
	this->_stats[Player::ARMOR]->setPercent(armor->getArmor());
	this->_stats[Player::SPEED]->setPercent(speed->getSpeed() + 25);
}

void	Player::unload()
{
	Widget::unload();
}

void	Player::draw(Engine::IRender* render)
{
}

//
// GETTER
//

void	Player::setLogin(std::string const &login)
{
	this->_login->setText(login);
}


bool	Player::isReady() const
{
	return (this->_ready->isChecked());
}

Engine::CheckBox*	Player::getReadyButton()
{
	return (this->_ready);
}