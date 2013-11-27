#include "PlayCreateState.hpp"
#include "State.hpp"
#include "Event.hpp"
#include "MouseEvent.hpp"
#include "WindowEvent.hpp"
#include "Core.hpp"
#include "ButtonCallback.hpp"
#include "Callback.hpp"
#include "Message.hpp"
#include "PlayCreateCallback.hpp"
#include "ScopeLock.hpp"
#include "TCPPacket.hpp"
#include "SFMLImage.hpp"
#include "SFMLAnimation.hpp"
#include "SFMLText.hpp"

//
// CTOR / DTOR
//

PlayCreateState::PlayCreateState()
	: AState(State::CONNECTION),
	_dataModule(0),
	_background(new Engine::Background("background", SFMLImage::PLAY_BACKGROUND)),
	_name(new Engine::TextBox("name", SFMLImage::TEXTBOX, SFMLImage::TEXTBOX_SELECTED, SFMLImage::TEXTBOX_HOVER, SFMLText::TEXTBOX, 10, "room name")),
	_private(new Engine::CheckBox("private", SFMLImage::CHECKBOX_CHECKED_NORMAL_PRIVATE, SFMLImage::CHECKBOX_CHECKED_CLICKED_PRIVATE, 
	SFMLImage::CHECKBOX_CHECKED_HOVER_PRIVATE,  SFMLImage::CHECKBOX_UNCHECKED_NORMAL_PRIVATE,  SFMLImage::CHECKBOX_UNCHECKED_CLICKED_PRIVATE,
	SFMLImage::CHECKBOX_UNCHECKED_HOVER_PRIVATE)),
	_password(new Engine::TextBox("password", SFMLImage::TEXTBOX, SFMLImage::TEXTBOX_SELECTED, SFMLImage::TEXTBOX_HOVER, SFMLText::TEXTBOX, 10, "password", '*')),
	_ok(new Engine::Button("ok", SFMLImage::BUTTON_OK, SFMLImage::BUTTON_CLICKED_OK, SFMLImage::BUTTON_HOVER_OK, State::ROOM)),
	_quit(new Engine::Button("quit", SFMLImage::BUTTON_QUIT, SFMLImage::BUTTON_CLICKED_QUIT, SFMLImage::BUTTON_HOVER_QUIT)),
	_settings(new Engine::Button("settings", SFMLImage::BUTTON_SETTINGS, SFMLImage::BUTTON_CLICKED_SETTINGS, SFMLImage::BUTTON_HOVER_SETTINGS, State::SETTINGS)),
	_back(new Engine::Button("back", SFMLImage::BUTTON_BACK, SFMLImage::BUTTON_CLICKED_BACK, SFMLImage::BUTTON_HOVER_BACK)),
	_loading(new Engine::Background("loading", SFMLAnimation::LOADING))
{

}

PlayCreateState::~PlayCreateState()
{

}

//
// LIFE-CYCLE
//

void	PlayCreateState::initialize()
{
	this->addChild(this->_background);
	this->addChild(this->_name);
	this->addChild(this->_private);
	this->addChild(this->_password);
	this->addChild(this->_quit);
	this->addChild(this->_settings);
	this->addChild(this->_loading);
	this->addChild(this->_back);
	this->addChild(this->_ok);
	Widget::initialize();
	this->_loading->hide();
	this->addEventListener(Engine::Event::WINDOW, Engine::WindowEvent::CLOSED, &Engine::Callback::quit);
	this->addEventListener(Engine::Event::NETWORK, Ultra::Converter::numberToString(Message::ROOM_STATE), Callback::PlayCreate::checkRoomState);
	if ((this->_dataModule = dynamic_cast<DataModule*>(Engine::Core::getInstance()->getModule(Engine::AModule::DATA))))
	{
		this->_back->removeEventListener(Engine::Event::MOUSE, Engine::MouseEvent::LEFT_CLICK);
		this->_back->addEventListener(Engine::Event::MOUSE, Engine::MouseEvent::LEFT_CLICK, &Engine::Callback::Button::back);
		this->_quit->removeEventListener(Engine::Event::MOUSE, Engine::MouseEvent::LEFT_CLICK);
		this->_quit->addEventListener(Engine::Event::MOUSE, Engine::MouseEvent::LEFT_CLICK, &Engine::Callback::Button::quit);
		this->_ok->removeEventListener(Engine::Event::MOUSE, Engine::MouseEvent::LEFT_CLICK);
		this->_ok->addEventListener(Engine::Event::MOUSE, Engine::MouseEvent::LEFT_CLICK, &Callback::PlayCreate::createOnClick);
		this->_loading->addEventListener(Engine::Event::MOUSE, Engine::MouseEvent::MOUSE_MOVE, &Engine::Callback::followMouse);
		this->resize(this->_dataModule->getAttr<size_t>("winWidth"), this->_dataModule->getAttr<size_t>("winHeight"));
	}
	this->_networkModule = dynamic_cast<NetworkModule*>(Engine::Core::getInstance()->getModule(Engine::AModule::NETWORK));
}

void	PlayCreateState::update()
{
	Widget::update();
	if (this->_name->getText() != "" && (this->_password->getText() != "" || !this->_private->isChecked()))
		this->_ok->unlock();
	else
		this->_ok->lock();
	(!this->_private->isChecked() ? this->_password->lock() : this->_password->unlock());
}

void	PlayCreateState::unload()
{
	this->removeEventListener(Engine::Event::WINDOW, Engine::WindowEvent::CLOSED);
	this->_loading->removeEventListener(Engine::Event::MOUSE, Engine::MouseEvent::MOUSE_MOVE);
	Widget::unload();
	this->removeAllChild();
}

void	PlayCreateState::reset()
{
	this->_name->setText("");
	this->_password->setText("");
}

void	PlayCreateState::reload()
{
}

//
// PUBLIC FUNCTION
//

void	PlayCreateState::createRoom()
{
	//this->_loading->show();

	Message *msg = new Message(Message::ROOM_CREATE);
	msg->setAttr("name", Ultra::Value(std::string(this->_name->getText())));
	msg->setAttr("password", Ultra::Value(std::string(this->_password->getText())));

	Ultra::ScopeLock lock(Engine::Core::getInstance()->access(Engine::AModule::NETWORK));
	this->_networkModule->addMessage(new TCPPacket(msg, NetworkModule::ROOM), ISocket::TCP);
}

void	PlayCreateState::goToRoom()
{
	this->_loading->hide();
	this->_ok->active();
}

void	PlayCreateState::displayError(std::string const &msg)
{
	this->_loading->hide();
	std::cerr << msg << std::endl;
}

void	PlayCreateState::resize(size_t width, size_t height)
{
	if (this->_dataModule)
	{
		size_t	fontSize = static_cast<size_t>(width * 2 / 100);
		// Loading
		this->_loading->setSize(46, 46);
		this->_loading->setPosition(width / 2, height / 2);
		// Background
		this->_background->setSize(width, height);
		this->_background->setPosition(0, 0);
		// Name textbox
		this->_name->setSize(width * 20 / 100, height * 6 / 100);
		this->_name->setPosition(width * 39 / 100, height * 40 / 100);
		this->_name->setTextSize(fontSize);
		this->_name->setTextPosition(15, 5);
		this->_name->setTextColor(Ultra::Color(208, 154, 58, 255));
		// Private checkbox
		this->_private->setSize(width * 14 / 100, height * 4 / 100);
		this->_private->setPosition(width * 39 / 100, height * 49 / 100);
		// Password textbox
		this->_password->setSize(width * 20 / 100, height * 6 / 100);
		this->_password->setPosition(width * 39 / 100, height * 54 / 100);
		this->_password->setTextSize(fontSize);
		this->_password->setTextPosition(15, 5);
		this->_password->setTextColor(Ultra::Color(208, 154, 58, 255));
		// Ok button
		this->_ok->setSize(width * 14 / 100, height * 4 / 100);
		this->_ok->setPosition(width * 42 / 100, height * 67 / 100);
		// Quit button
		this->_quit->setSize(width * 9 / 100, height * 3 / 100);
		this->_quit->setPosition(width * 90 / 100, height * 1 / 100);
		// Back button
		this->_back->setSize(width * 9 / 100, height * 3 / 100);
		this->_back->setPosition((size_t)((float)width * 1.5 / 100), (size_t)((float)height * 96.5 / 100));
		// Settings button
		this->_settings->setSize(width * 9 / 100, height * 3 / 100);
		this->_settings->setPosition(width * 90 / 100, (size_t)((float)height * 4.5 / 100));
	}
}