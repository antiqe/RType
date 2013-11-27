#include "SettingsState.hpp"
#include "State.hpp"
#include "Event.hpp"
#include "MouseEvent.hpp"
#include "WindowEvent.hpp"
#include "Core.hpp"
#include "ButtonCallback.hpp"
#include "Callback.hpp"
//#include "SettingsStateCallback.hpp"
#include "Message.hpp"
#include "HSlider.hpp"

//
// CTOR / DTOR
//

SettingsState::SettingsState()
	: AState(State::CONNECTION),
	_dataModule(0),
	_background(new Engine::Background("background", SFMLImage::SETTINGS_BACKGROUND)),
	_ambient(new Engine::HSlider("ambient", SFMLImage::HSLIDER, SFMLImage::SLIDER_CURSOR_NORMAL,
	SFMLImage::SLIDER_CURSOR_CLICKED, SFMLImage::SLIDER_CURSOR_HOVER)),
	_effect(new Engine::HSlider("effect", SFMLImage::HSLIDER, SFMLImage::SLIDER_CURSOR_NORMAL,
	SFMLImage::SLIDER_CURSOR_CLICKED, SFMLImage::SLIDER_CURSOR_HOVER)),
	_global(new Engine::HSlider("global", SFMLImage::HSLIDER, SFMLImage::SLIDER_CURSOR_NORMAL,
	SFMLImage::SLIDER_CURSOR_CLICKED, SFMLImage::SLIDER_CURSOR_HOVER)),
	_resolution(new Engine::HSlider("resolution", SFMLImage::HSLIDER, SFMLImage::SLIDER_CURSOR_NORMAL,
	SFMLImage::SLIDER_CURSOR_CLICKED, SFMLImage::SLIDER_CURSOR_HOVER)),
	_fullscreen(new Engine::CheckBox("fullscreen", SFMLImage::CHECKBOX_CHECKED_NORMAL, SFMLImage::CHECKBOX_CHECKED_CLICKED, SFMLImage::CHECKBOX_CHECKED_HOVER,
	SFMLImage::CHECKBOX_UNCHECKED_NORMAL, SFMLImage::CHECKBOX_UNCHECKED_CLICKED, SFMLImage::CHECKBOX_UNCHECKED_HOVER)),
	_quit(new Engine::Button("quit", SFMLImage::BUTTON_QUIT, SFMLImage::BUTTON_CLICKED_QUIT, SFMLImage::BUTTON_HOVER_QUIT)),
	_settings(new Engine::Button("settings", SFMLImage::BUTTON_SETTINGS, SFMLImage::BUTTON_CLICKED_SETTINGS, SFMLImage::BUTTON_HOVER_SETTINGS, State::SETTINGS)),
	_back(new Engine::Button("quit", SFMLImage::BUTTON_BACK, SFMLImage::BUTTON_CLICKED_BACK, SFMLImage::BUTTON_HOVER_BACK)),
	_loading(new Engine::Background("loading", SFMLAnimation::LOADING))
{

}

SettingsState::~SettingsState()
{

}

//
// LIFE-CYCLE
//

void	SettingsState::initialize()
{
	this->addChild(this->_background);
	this->addChild(this->_ambient);
	this->addChild(this->_effect);
	this->addChild(this->_global);
	this->addChild(this->_resolution);
	this->addChild(this->_fullscreen);
	this->addChild(this->_quit);
	this->addChild(this->_settings);
	this->addChild(this->_loading);
	this->addChild(this->_back);
	Widget::initialize();
	this->_loading->hide();
	this->addEventListener(Engine::Event::WINDOW, Engine::WindowEvent::CLOSED, &Engine::Callback::quit);
	//this->addEventListener(Engine::Event::NETWORK, Ultra::Converter::numberToString(Message::AUTH_???));
	if ((this->_dataModule = dynamic_cast<DataModule*>(Engine::Core::getInstance()->getModule(Engine::AModule::DATA))))
	{
		size_t	width = this->_dataModule->getAttr<size_t>("winWidth");
		size_t	height = this->_dataModule->getAttr<size_t>("winHeight");
		/*		size_t	fontSize = static_cast<size_t>(width * 2.5 / 100);*/

		// Loading
		this->_loading->setSize(46, 46);
		this->_loading->setPosition(width / 2, height / 2);
		this->_loading->addEventListener(Engine::Event::MOUSE, Engine::MouseEvent::MOUSE_MOVE, &Engine::Callback::followMouse);
		// Background
		this->_background->setSize(width, height);
		this->_background->setPosition(0, 0);
		// Ambient Slider
		this->_ambient->setSize(width * 13 / 100, height * 2 / 100);
		this->_ambient->setPosition(width * 37 / 100, height * 57 / 100);
		// Effect Slider
		this->_effect->setSize(width * 13 / 100, height * 2 / 100);
		this->_effect->setPosition(width * 62 / 100, height * 57 / 100);
		// Global Slider
		this->_global->setSize(width * 13 / 100, height * 2 / 100);
		this->_global->setPosition(width * 44 / 100, height * 65 / 100);
		// Resolution Slider
		this->_resolution->setSize(width * 13 / 100, height * 2 / 100);
		this->_resolution->setPosition(width * 40 / 100, (size_t)((float)(height) * 83.5 / 100));
		// Fullscreen Slider
		this->_fullscreen->setSize(width * 2 / 100, height * 3 / 100);
		this->_fullscreen->setPosition(width * 69 / 100, (size_t)((float)(height) * 82.75 / 100));
		// Quit button
		this->_quit->setSize(width * 9 / 100, height * 3 / 100);
		this->_quit->setPosition(width * 90 / 100, height * 1 / 100);
		this->_quit->removeEventListener(Engine::Event::MOUSE, Engine::MouseEvent::LEFT_CLICK);
		this->_quit->addEventListener(Engine::Event::MOUSE, Engine::MouseEvent::LEFT_CLICK, &Engine::Callback::Button::quit);
		// Back button
		this->_back->setSize(width * 9 / 100, height * 3 / 100);
		this->_back->setPosition((int)((float)width * 1.5 / 100), (int)((float)height * 96.5 / 100));
		this->_back->removeEventListener(Engine::Event::MOUSE, Engine::MouseEvent::LEFT_CLICK);
		this->_back->addEventListener(Engine::Event::MOUSE, Engine::MouseEvent::LEFT_CLICK, &Engine::Callback::Button::back);
		// Settings button
		this->_settings->setSize(width * 9 / 100, height * 3 / 100);
		this->_settings->setPosition((int)((float)width * 90.0f / 100.0f), (int)((float)height * 4.5f / 100.0f));
	}
}

void	SettingsState::update()
{
	Widget::update();
}

void	SettingsState::unload()
{
	this->removeEventListener(Engine::Event::WINDOW, Engine::WindowEvent::CLOSED);
	this->_loading->removeEventListener(Engine::Event::MOUSE, Engine::MouseEvent::MOUSE_MOVE);
	Widget::unload();
	this->removeAllChild();
}

void	SettingsState::reset()
{
}

void	SettingsState::reload()
{
}
