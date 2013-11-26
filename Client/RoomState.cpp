#include "RoomState.hpp"
#include "State.hpp"
#include "Event.hpp"
#include "MouseEvent.hpp"
#include "WindowEvent.hpp"
#include "Core.hpp"
#include "ButtonCallback.hpp"
#include "NetworkModule.hpp"
#include "RoomStateCallback.hpp"
#include "StatePlayer.hpp"
#include "Callback.hpp"
#include "Message.hpp"
#include "SFMLText.hpp"
#include "TCPPacket.hpp"

//
// CTOR / DTOR
//

RoomState::RoomState()
	: AState(State::CONNECTION),
	_dataModule(0),
	_background(new Engine::Background("background", SFMLImage::ROOM_BACKGROUND)),
	_go(new Engine::Button("go", SFMLImage::BUTTON_GO, SFMLImage::BUTTON_CLICKED_GO, SFMLImage::BUTTON_HOVER_GO, State::GAME)),
	_chatBox(new Engine::ListBox("chatBox", SFMLImage::LISTBOX_EVEN, SFMLImage::LISTBOX_ODD, SFMLImage::LISTBOX_FOCUS, SFMLImage::SLIDER,
	SFMLImage::SLIDER_CURSOR_NORMAL, SFMLImage::SLIDER_CURSOR_CLICKED, SFMLImage::SLIDER_CURSOR_HOVER, 8, SFMLText::TEXTBOX)),
	_msg(new Engine::TextBox("msg", SFMLImage::TEXTBOX, SFMLImage::TEXTBOX_SELECTED, SFMLImage::TEXTBOX_HOVER, SFMLText::TEXTBOX, 64, "message")),
	_send(new Engine::Button("send", SFMLImage::BUTTON_SEND, SFMLImage::BUTTON_CLICKED_SEND, SFMLImage::BUTTON_HOVER_SEND)),
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
	this->addChild(this->_quit);
	this->addChild(this->_settings);
	this->addChild(this->_loading);
	this->addChild(this->_back);
	this->addChild(this->_go);
	this->addChild(this->_chatBox);
	this->addChild(this->_msg);
	this->addChild(this->_send);
	Widget::initialize();
	this->_loading->hide();
	this->addEventListener(Engine::Event::WINDOW, Engine::WindowEvent::CLOSED, &Engine::Callback::quit);
	if ((this->_dataModule = dynamic_cast<DataModule*>(Engine::Core::getInstance()->getModule(Engine::AModule::DATA))))
	{
		size_t	width = this->_dataModule->getAttr<size_t>("winWidth");
		size_t	height = this->_dataModule->getAttr<size_t>("winHeight");

		// Loading
		this->_loading->setSize(46, 46);
		this->_loading->setPosition(width / 2, height / 2);
		this->_loading->addEventListener(Engine::Event::MOUSE, Engine::MouseEvent::MOUSE_MOVE, &Engine::Callback::followMouse);
		// Background
		this->_background->setSize(width, height);
		this->_background->setPosition(0, 0);
		// Go button
		this->_go->setSize(width * 5 / 100, height * 7 / 100);
		this->_go->setPosition(width * 48.33 / 100, height * 37 / 100);
		// Chatbox button
		this->_chatBox->setSize(width * 47.50 / 100, height * 20 / 100);
		this->_chatBox->setPosition(width * 26.45 / 100, height * 71 / 100);
		this->_chatBox->setTextColor(Ultra::Color(138, 212, 241, 255));
		this->_chatBox->setFocusTextColor(Ultra::Color(196, 232, 249, 255));
		this->_chatBox->setTextStyle(0);
		this->_chatBox->setScrollWidth(width * 1.50 / 100);

		this->_chatBox->push("salut les amis", 42, true);
		this->_chatBox->push("je suis echo le dauphin", 42, true);
		this->_chatBox->push("je connais toto", 42, true);
		this->_chatBox->push("salut les amis", 42, true);
		this->_chatBox->push("je suis echo le dauphin", 42, true);
		this->_chatBox->push("je connais toto", 42, true);
		this->_chatBox->push("salut les amis", 42, true);
		this->_chatBox->push("je suis echo le dauphin", 42, true);
		this->_chatBox->push("je connais toto", 42, true);
		this->_chatBox->push("salut les amis", 42, true);
		this->_chatBox->push("je suis echo le dauphin", 42, true);
		this->_chatBox->push("je connais toto", 42, true);
		this->_chatBox->push("salut les amis", 42, true);
		this->_chatBox->push("je suis echo le dauphin", 42, true);
		this->_chatBox->push("je connais toto", 42, true);
		this->_chatBox->push("salut les amis", 42, true);
		this->_chatBox->push("je suis echo le dauphin", 42, true);
		this->_chatBox->push("je connais toto", 42, true);
		this->_chatBox->push("salut les amis", 42, true);
		this->_chatBox->push("je suis echo le dauphin", 42, true);
		this->_chatBox->push("je connais toto", 42, true);
		this->_chatBox->push("salut les amis", 42, true);
		this->_chatBox->push("je suis echo le dauphin", 42, true);
		this->_chatBox->push("je connais toto", 42, true);
		// Msg textbox
		this->_msg->setSize(width * 40 / 100, height * 2.5 / 100);
		this->_msg->setPosition(width * 26.45 / 100, height * 91 / 100);
		this->_msg->setTextSize(static_cast<size_t>(width * 1 / 100));
		this->_msg->setTextPosition(15, 0);
		this->_msg->setTextColor(Ultra::Color(208, 154, 58, 255));
		// Send button
		this->_send->setSize(width * 7.5 / 100, height * 2.5 / 100);
		this->_send->setPosition(width * 67.45 / 100, height * 91 / 100);
		// Quit button
		this->_quit->setSize(width * 9 / 100, height * 3 / 100);
		this->_quit->setPosition(width * 90 / 100, height * 1 / 100);
		this->_quit->removeEventListener(Engine::Event::MOUSE, Engine::MouseEvent::LEFT_CLICK);
		this->_quit->addEventListener(Engine::Event::MOUSE, Engine::MouseEvent::LEFT_CLICK, &Engine::Callback::Button::quit);
		// Back button
		this->_back->setSize(width * 9 / 100, height * 3 / 100);
		this->_back->setPosition(width * 1.5 / 100, height * 96.5 / 100);
		this->_back->removeEventListener(Engine::Event::MOUSE, Engine::MouseEvent::LEFT_CLICK);
		this->_back->addEventListener(Engine::Event::MOUSE, Engine::MouseEvent::LEFT_CLICK, &Callback::Room::backOnClick);
		// Settings button
		this->_settings->setSize(width * 9 / 100, height * 3 / 100);
		this->_settings->setPosition(width * 90 / 100, height * 4.5 / 100);
	}
	this->_networkModule = dynamic_cast<NetworkModule*>(Engine::Core::getInstance()->getModule(Engine::AModule::NETWORK));
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

void	RoomState::quitRoom()
{
	Message *msg = new Message(Message::ROOM_PLAYER_INFO);

	msg->setAttr("id_player", Ultra::Value((char)this->_networkModule->getSock()));
	msg->setAttr("name", Ultra::Value(std::string("")));
	msg->setAttr("id_ship", Ultra::Value((char)0));
	msg->setAttr("state", Ultra::Value((char)Network::LEFT));

	this->_networkModule->addMessage(new TCPPacket(msg, NetworkModule::ROOM), ISocket::TCP);
}
