#include "PlayJoinState.hpp"
#include "State.hpp"
#include "Event.hpp"
#include "MouseEvent.hpp"
#include "WindowEvent.hpp"
#include "Core.hpp"
#include "ButtonCallback.hpp"
#include "Callback.hpp"
#include "PlayJoinCallback.hpp"
#include "Message.hpp"
#include "TCPPacket.hpp"
#include "ScopeLock.hpp"
#include "SFMLImage.hpp"
#include "SFMLAnimation.hpp"
#include "SFMLText.hpp"

//
// CTOR / DTOR
//

PlayJoinState::PlayJoinState()
	: AState(State::CONNECTION),
	_dataModule(0),
	_background(new Engine::Background("background", SFMLImage::JOIN_BACKGROUND)),
	_list(new Engine::ListBox<RoomInfo *>("list", SFMLImage::LISTBOX_EVEN, SFMLImage::LISTBOX_ODD, SFMLImage::LISTBOX_FOCUS, SFMLImage::SLIDER,
	SFMLImage::SLIDER_CURSOR_NORMAL, SFMLImage::SLIDER_CURSOR_CLICKED, SFMLImage::SLIDER_CURSOR_HOVER, 15, SFMLText::TEXTBOX)),
	_select(new Engine::Button("select", SFMLImage::BUTTON_SELECT, SFMLImage::BUTTON_CLICKED_SELECT, SFMLImage::BUTTON_HOVER_SELECT, State::ROOM)),
	_refresh(new Engine::Button("refresh", SFMLImage::BUTTON_REFRESH, SFMLImage::BUTTON_CLICKED_REFRESH, SFMLImage::BUTTON_HOVER_REFRESH)),
	_quit(new Engine::Button("quit", SFMLImage::BUTTON_QUIT, SFMLImage::BUTTON_CLICKED_QUIT, SFMLImage::BUTTON_HOVER_QUIT)),
	_settings(new Engine::Button("settings", SFMLImage::BUTTON_SETTINGS, SFMLImage::BUTTON_CLICKED_SETTINGS, SFMLImage::BUTTON_HOVER_SETTINGS, State::SETTINGS)),
	_back(new Engine::Button("back", SFMLImage::BUTTON_BACK, SFMLImage::BUTTON_CLICKED_BACK, SFMLImage::BUTTON_HOVER_BACK)),
	_loading(new Engine::Background("loading", SFMLAnimation::LOADING))
{
}

PlayJoinState::~PlayJoinState()
{
}

//
// LIFE-CYCLE
//

void	PlayJoinState::initialize()
{
	this->addChild(this->_background);
	this->addChild(this->_list);
	this->addChild(this->_select);
	this->addChild(this->_quit);
	this->addChild(this->_settings);
	this->addChild(this->_loading);
	this->addChild(this->_back);
	this->addChild(this->_refresh);
	Widget::initialize();
	this->_loading->hide();
	this->addEventListener(Engine::Event::WINDOW, Engine::WindowEvent::CLOSED, &Engine::Callback::quit);
	this->addEventListener(Engine::Event::NETWORK, Ultra::Converter::numberToString(Message::ROOM_INFO), Callback::PlayJoin::getRoomInfo);
	this->addEventListener(Engine::Event::NETWORK, Ultra::Converter::numberToString(Message::ROOM_STATE), Callback::PlayJoin::onRoomState);
	if ((this->_dataModule = dynamic_cast<DataModule*>(Engine::Core::getInstance()->getModule(Engine::AModule::DATA))))
	{
		this->resize(this->_dataModule->getAttr<size_t>("winWidth"), this->_dataModule->getAttr<size_t>("winHeight"));
		this->_loading->addEventListener(Engine::Event::MOUSE, Engine::MouseEvent::MOUSE_MOVE, &Engine::Callback::followMouse);
		this->_select->removeEventListener(Engine::Event::MOUSE, Engine::MouseEvent::LEFT_CLICK);
		this->_select->addEventListener(Engine::Event::MOUSE, Engine::MouseEvent::LEFT_CLICK, &Callback::PlayJoin::selectOnClick);
		this->_quit->removeEventListener(Engine::Event::MOUSE, Engine::MouseEvent::LEFT_CLICK);
		this->_quit->addEventListener(Engine::Event::MOUSE, Engine::MouseEvent::LEFT_CLICK, &Engine::Callback::Button::quit);
		this->_back->removeEventListener(Engine::Event::MOUSE, Engine::MouseEvent::LEFT_CLICK);
		this->_back->addEventListener(Engine::Event::MOUSE, Engine::MouseEvent::LEFT_CLICK, &Engine::Callback::Button::back);
		this->_refresh->removeEventListener(Engine::Event::MOUSE, Engine::MouseEvent::LEFT_CLICK);
		this->_refresh->addEventListener(Engine::Event::MOUSE, Engine::MouseEvent::LEFT_CLICK, &Callback::PlayJoin::refreshOnClick);
	}
	this->_networkModule = dynamic_cast<NetworkModule*>(Engine::Core::getInstance()->getModule(Engine::AModule::NETWORK));
}

void	PlayJoinState::update()
{
	Widget::update();
}

void	PlayJoinState::unload()
{
	this->removeEventListener(Engine::Event::WINDOW, Engine::WindowEvent::CLOSED);
	this->_loading->removeEventListener(Engine::Event::MOUSE, Engine::MouseEvent::MOUSE_MOVE);
	Widget::unload();
	this->removeAllChild();
}

void	PlayJoinState::reset()
{
	this->refresh();
}

void	PlayJoinState::reload()
{
}

void	PlayJoinState::roomListRequest()
{
	Ultra::ScopeLock lc(Engine::Core::getInstance()->access(Engine::AModule::NETWORK));
	this->_networkModule->addMessage(new TCPPacket(new Message(Message::ROOM_LIST), NetworkModule::ROOM), ISocket::TCP);
}

void	PlayJoinState::refresh()
{
	this->_list->clear();
	this->roomListRequest();
}

void	PlayJoinState::selectServer()
{
	if ((int)this->_list->getFocusLine() != -1)
	{
		RoomInfo *rm = this->_list->getFocusData();
		Message *msg = new Message(Message::ROOM_JOIN);

		msg->setAttr("id", Ultra::Value((unsigned short)rm->getID()));
		msg->setAttr("password", Ultra::Value(std::string("")));
		this->_networkModule->addMessage(new TCPPacket(msg, NetworkModule::ROOM), ISocket::TCP);
	}
}

void	PlayJoinState::goToRoom()
{
	this->_loading->hide();
	this->_select->active();
}

void	PlayJoinState::resize(size_t width, size_t height)
{
	if (this->_dataModule)
	{
		// Loading
		this->_loading->setSize(46, 46);
		this->_loading->setPosition(width / 2, height / 2);
		// Background
		this->_background->setSize(width, height);
		this->_background->setPosition(0, 0);
		// List textbox
		this->_list->setSize((size_t)((float)width * 47.85 / 100), height * 55 / 100);
		this->_list->setPosition((size_t)((float)width * 25.45 / 100), height * 30 / 100);
		this->_list->setTextColor(Ultra::Color(138, 212, 241, 255));
		this->_list->setFocusTextColor(Ultra::Color(196, 232, 249, 255));
		this->_list->setTextStyle(0);
		this->_list->setScrollWidth(width * 2 / 100);
		// Select button
		this->_select->setSize(width * 14 / 100, height * 4 / 100);
		this->_select->setPosition(width * 42 / 100, height * 88 / 100);
		// Quit button
		this->_quit->setSize(width * 9 / 100, height * 3 / 100);
		this->_quit->setPosition(width * 90 / 100, height * 1 / 100);
		// Back button
		this->_back->setSize(width * 9 / 100, height * 3 / 100);
		this->_back->setPosition((size_t)((float)width * 1.5 / 100), (size_t)((float)height * 96.5 / 100));
		// Refresh button
		this->_refresh->setSize(width * 9 / 100, height * 3 / 100);
		this->_refresh->setPosition((size_t)((float)width * 90 / 100), (size_t)((float)height * 96.5 / 100));
		// Settings button
		this->_settings->setSize(width * 9 / 100, height * 3 / 100);
		this->_settings->setPosition(width * 90 / 100, (size_t)((float)height * 4.5 / 100));
	}
}