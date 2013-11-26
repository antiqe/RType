#include "RoomState.hpp"
#include "State.hpp"
#include "Event.hpp"
#include "MouseEvent.hpp"
#include "WindowEvent.hpp"
#include "Core.hpp"
#include "ButtonCallback.hpp"
#include "Callback.hpp"
#include "Message.hpp"
#include "SFMLImage.hpp"
#include "SFMLText.hpp"
#include "SFMLAnimation.hpp"

//
// CTOR / DTOR
//

RoomState::RoomState()
	: AState(State::CONNECTION),
	_dataModule(0),
	_background(new Engine::Background("background", SFMLImage::PLAY_BACKGROUND)),
	_create(new Engine::Button("create", SFMLImage::BUTTON_CREATE, SFMLImage::BUTTON_CLICKED_CREATE, SFMLImage::BUTTON_HOVER_CREATE, State::PLAY_CREATE)),
	_join(new Engine::Button("join", SFMLImage::BUTTON_JOIN, SFMLImage::BUTTON_CLICKED_JOIN, SFMLImage::BUTTON_HOVER_JOIN, State::PLAY_JOIN)),
	_quit(new Engine::Button("quit", SFMLImage::BUTTON_QUIT, SFMLImage::BUTTON_CLICKED_QUIT, SFMLImage::BUTTON_HOVER_QUIT)),
	_settings(new Engine::Button("settings", SFMLImage::BUTTON_SETTINGS, SFMLImage::BUTTON_CLICKED_SETTINGS, SFMLImage::BUTTON_HOVER_SETTINGS, State::SETTINGS)),
	_back(new Engine::Button("back", SFMLImage::BUTTON_BACK, SFMLImage::BUTTON_CLICKED_BACK, SFMLImage::BUTTON_HOVER_BACK)),
	_loading(new Engine::Background("loading", SFMLAnimation::LOADING))
{
}

RoomState::~RoomState()
{
}

//
// LIFE-CYCLE
//

void	RoomState::initialize()
{
	this->addChild(this->_background);
	this->addChild(this->_create);
	this->addChild(this->_join);
	this->addChild(this->_quit);
	this->addChild(this->_settings);
	this->addChild(this->_loading);
	this->addChild(this->_back);
	Widget::initialize();
	this->_loading->hide();
	this->addEventListener(Engine::Event::WINDOW, Engine::WindowEvent::CLOSED, &Engine::Callback::quit);
	if ((this->_dataModule = dynamic_cast<DataModule*>(Engine::Core::getInstance()->getModule(Engine::AModule::DATA))))
	{
		size_t	width = this->_dataModule->getAttr<size_t>("winWidth");
		size_t	height = this->_dataModule->getAttr<size_t>("winHeight");
		size_t	fontSize = static_cast<size_t>(width * 2.5 / 100);

		// Loading
		this->_loading->setSize(46, 46);
		this->_loading->setPosition(width / 2, height / 2);
		this->_loading->addEventListener(Engine::Event::MOUSE, Engine::MouseEvent::MOUSE_MOVE, &Engine::Callback::followMouse);
		// Background
		this->_background->setSize(width, height);
		this->_background->setPosition(0, 0);
		// Create button
		this->_create->setSize(width * 20 / 100, height * 6 / 100);
		this->_create->setPosition(width * 39 / 100, height * 48 / 100);	
		// Join button
		this->_join->setSize(width * 20 / 100, height * 6 / 100);
		this->_join->setPosition(width * 39 / 100, height * 58 / 100);	
		// Quit button
		this->_quit->setSize(width * 9 / 100, height * 3 / 100);
		this->_quit->setPosition(width * 90 / 100, height * 1 / 100);
		this->_quit->removeEventListener(Engine::Event::MOUSE, Engine::MouseEvent::LEFT_CLICK);
		this->_quit->addEventListener(Engine::Event::MOUSE, Engine::MouseEvent::LEFT_CLICK, &Engine::Callback::Button::quit);
		// Back button
		this->_back->setSize(width * 9 / 100, height * 3 / 100);
		this->_back->setPosition(width * 1.5 / 100, height * 96.5 / 100);
		this->_back->removeEventListener(Engine::Event::MOUSE, Engine::MouseEvent::LEFT_CLICK);
		this->_back->addEventListener(Engine::Event::MOUSE, Engine::MouseEvent::LEFT_CLICK, &Engine::Callback::Button::back);
		// Settings button
		this->_settings->setSize(width * 9 / 100, height * 3 / 100);
		this->_settings->setPosition(width * 90 / 100, height * 4.5 / 100);
	}
}

void	RoomState::update()
{
	Widget::update();
}

void	RoomState::unload()
{
	this->removeEventListener(Engine::Event::WINDOW, Engine::WindowEvent::CLOSED);
	this->_loading->removeEventListener(Engine::Event::MOUSE, Engine::MouseEvent::MOUSE_MOVE);
	Widget::unload();
	this->removeAllChild();
}

void	RoomState::reset()
{
}

void	RoomState::reload()
{
}
