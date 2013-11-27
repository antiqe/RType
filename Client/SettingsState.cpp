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
#include "SFMLText.hpp"
#include "Core.hpp"
#include "ScopeLock.hpp"
#include "Configuration.hpp"

//
// CTOR / DTOR
//

SettingsState::SettingsState()
	: AState(State::CONNECTION),
	_dataModule(0),
	_background(new Engine::Background("background", SFMLImage::SETTINGS_BACKGROUND)),
	_moveUp(new Engine::KeyBox("moveup", SFMLImage::TEXTBOX, SFMLImage::TEXTBOX, SFMLImage::TEXTBOX_HOVER, SFMLText::TEXTBOX, 1)),
	_moveDown(new Engine::KeyBox("movedown", SFMLImage::TEXTBOX, SFMLImage::TEXTBOX, SFMLImage::TEXTBOX_HOVER, SFMLText::TEXTBOX, 1)),
	_moveLeft(new Engine::KeyBox("moveleft", SFMLImage::TEXTBOX, SFMLImage::TEXTBOX, SFMLImage::TEXTBOX_HOVER, SFMLText::TEXTBOX, 1)),
	_moveRight(new Engine::KeyBox("moveright", SFMLImage::TEXTBOX, SFMLImage::TEXTBOX, SFMLImage::TEXTBOX_HOVER, SFMLText::TEXTBOX, 1)),
	_shoot(new Engine::KeyBox("shoot", SFMLImage::TEXTBOX, SFMLImage::TEXTBOX, SFMLImage::TEXTBOX_HOVER, SFMLText::TEXTBOX, 1)),
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
	this->addChild(this->_moveUp);
	this->addChild(this->_moveDown);
	this->addChild(this->_moveLeft);
	this->addChild(this->_moveRight);
	this->addChild(this->_shoot);
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
	if ((this->_dataModule = dynamic_cast<DataModule*>(Engine::Core::getInstance()->getModule(Engine::AModule::DATA))))
	{
		this->resize(this->_dataModule->getAttr<size_t>("winWidth"), this->_dataModule->getAttr<size_t>("winHeight"));
		this->_loading->addEventListener(Engine::Event::MOUSE, Engine::MouseEvent::MOUSE_MOVE, &Engine::Callback::followMouse);
		this->_ambient->removeEventListener(Engine::Event::MOUSE, Engine::MouseEvent::MOUSE_WHEEL);
		this->_effect->removeEventListener(Engine::Event::MOUSE, Engine::MouseEvent::MOUSE_WHEEL);
		this->_global->removeEventListener(Engine::Event::MOUSE, Engine::MouseEvent::MOUSE_WHEEL);
		this->_resolution->removeEventListener(Engine::Event::MOUSE, Engine::MouseEvent::MOUSE_WHEEL);
		this->_moveUp->addCharacter(static_cast<Engine::Keyboard::Key>(this->_dataModule->getAttr<int>("upKey")));
		this->_moveDown->addCharacter(static_cast<Engine::Keyboard::Key>(this->_dataModule->getAttr<int>("downKey")));
		this->_moveLeft->addCharacter(static_cast<Engine::Keyboard::Key>(this->_dataModule->getAttr<int>("leftKey")));
		this->_moveRight->addCharacter(static_cast<Engine::Keyboard::Key>(this->_dataModule->getAttr<int>("rightKey")));
		this->_shoot->addCharacter(static_cast<Engine::Keyboard::Key>(this->_dataModule->getAttr<int>("shootKey")));
		this->_ambient->setValue(this->_dataModule->getAttr<int>("ambientSound"));
		this->_effect->setValue(this->_dataModule->getAttr<int>("effectSound"));
		this->_global->setValue(this->_dataModule->getAttr<int>("globalSound"));
		this->_resolution->setValue((int)(Configuration::SCALE * 100));
		if (this->_dataModule->getAttr<unsigned long>("winMode") == sf::Style::Fullscreen)
			this->_fullscreen->toggle();
		this->_quit->removeEventListener(Engine::Event::MOUSE, Engine::MouseEvent::LEFT_CLICK);
		this->_quit->addEventListener(Engine::Event::MOUSE, Engine::MouseEvent::LEFT_CLICK, &Engine::Callback::Button::quit);
		this->_back->removeEventListener(Engine::Event::MOUSE, Engine::MouseEvent::LEFT_CLICK);
		this->_back->addEventListener(Engine::Event::MOUSE, Engine::MouseEvent::LEFT_CLICK, &Engine::Callback::Button::back);
		this->_settings->removeEventListener(Engine::Event::MOUSE, Engine::MouseEvent::LEFT_CLICK);
		this->_settings->lock();
	}
}

void	SettingsState::update()
{
	Widget::update();
	Ultra::ScopeLock	lock(Engine::Core::getInstance()->access(Engine::AModule::DATA));
	//this->_dataModule->setAttr("upKey", Ultra::Value(this->_moveUp));
	//this->_dataModule->setAttr("downKey", Ultra::Value(this->_moveDown));
	//this->_dataModule->setAttr("leftKey", Ultra::Value(this->_moveLeft));
	//this->_dataModule->setAttr("rightKey", Ultra::Value(this->_moveRight));
	//this->_dataModule->setAttr("shootKey", Ultra::Value(this->_shoot));
	this->_dataModule->setAttr("globalSound", Ultra::Value((int)this->_global->getValue()));
	this->_dataModule->setAttr("ambientSound", Ultra::Value((int)this->_ambient->getValue()));
	this->_dataModule->setAttr("effectSound", Ultra::Value((int)this->_effect->getValue()));
	/*if (this->_fullscreen->isChecked())
		this->_dataModule->setAttr("winMode", Ultra::Value((unsigned long)8)); 
	else
	{
		this->_dataModule->setAttr("winWidth", Ultra::Value((size_t)(((float)this->_resolution->getValue()) / 100.0f * 1600.0f)));
		this->_dataModule->setAttr("winHeight", Ultra::Value((size_t)(((float)this->_resolution->getValue()) / 100.0f * 900.0f)));
		this->_dataModule->setAttr("winMode", Ultra::Value((unsigned long)5)); 
	}*/
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

void	SettingsState::resize(size_t width, size_t height)
{
	if (this->_dataModule)
	{
		size_t	fontSize = (size_t)((float)(width * 1.5 / 100));
		// Loading
		this->_loading->setSize(46, 46);
		this->_loading->setPosition(width / 2, height / 2);
		// Background
		this->_background->setSize(width, height);
		this->_background->setPosition(0, 0);
		// Moveup keybox
		this->_moveUp->setSize(width * 8 / 100, height * 4 / 100);
		this->_moveUp->setPosition(width * 40 / 100, (int)((float)height * 28.50 / 100));
		this->_moveUp->setTextSize(fontSize);
		this->_moveUp->setTextPosition(15, 5);
		this->_moveUp->setTextColor(Ultra::Color(208, 154, 58, 255));
		// Movedown keybox
		this->_moveDown->setSize(width * 8 / 100, height * 4 / 100);
		this->_moveDown->setPosition(width * 65 / 100, (int)((float)height * 28.50 / 100));
		this->_moveDown->setTextSize(fontSize);
		this->_moveDown->setTextPosition(15, 5);
		this->_moveDown->setTextColor(Ultra::Color(208, 154, 58, 255));
		// MoveLeft keybox
		this->_moveLeft->setSize(width * 8 / 100, height * 4 / 100);
		this->_moveLeft->setPosition(width * 40 / 100, (int)((float)height * 34 / 100));
		this->_moveLeft->setTextSize(fontSize);
		this->_moveLeft->setTextPosition(15, 5);
		this->_moveLeft->setTextColor(Ultra::Color(208, 154, 58, 255));
		// MoveRight keybox
		this->_moveRight->setSize(width * 8 / 100, height * 4 / 100);
		this->_moveRight->setPosition(width * 65 / 100, (int)((float)height * 34 / 100));
		this->_moveRight->setTextSize(fontSize);
		this->_moveRight->setTextPosition(15, 5);
		this->_moveRight->setTextColor(Ultra::Color(208, 154, 58, 255));
		// Shoot keybox
		this->_shoot->setSize(width * 8 / 100, height * 4 / 100);
		this->_shoot->setPosition(width * 40 / 100, (int)((float)height * 39.50 / 100));
		this->_shoot->setTextSize(fontSize);
		this->_shoot->setTextPosition(15, 5);
		this->_shoot->setTextColor(Ultra::Color(208, 154, 58, 255));
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
		// Back button
		this->_back->setSize(width * 9 / 100, height * 3 / 100);
		this->_back->setPosition((int)((float)width * 1.5 / 100), (int)((float)height * 96.5 / 100));
		// Settings button
		this->_settings->setSize(width * 9 / 100, height * 3 / 100);
		this->_settings->setPosition((int)((float)width * 90.0f / 100.0f), (int)((float)height * 4.5f / 100.0f));
	}
}