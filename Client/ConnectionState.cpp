#include "ConnectionState.hpp"
#include "State.hpp"
#include "Event.hpp"
#include "MouseEvent.hpp"
#include "WindowEvent.hpp"
#include "Core.hpp"
#include "ButtonCallback.hpp"
#include "ConnectionCallback.hpp"
#include "Message.hpp"
#include "SFMLAnimation.hpp"
#include "SFMLImage.hpp"
#include "SFMLText.hpp"
#include "TCPPacket.hpp"
#include "ScopeLock.hpp"
#include "ISocket.hpp"
#include "MD5encode.hpp"

//
// CTOR / DTOR
//

ConnectionState::ConnectionState()
	: AState(State::CONNECTION),
	_dataModule(0),
	_networkModule(0),
	_background(new Engine::Background("background", SFMLImage::CONNECTION_BACKGROUND)),
	_connection(new Engine::Button("connection", SFMLImage::BUTTON_LOGIN, SFMLImage::BUTTON_CLICKED_LOGIN, SFMLImage::BUTTON_HOVER_LOGIN, State::PLAY)),
	_login(new Engine::TextBox("login", SFMLImage::TEXTBOX, SFMLImage::TEXTBOX_SELECTED, SFMLImage::TEXTBOX_HOVER, SFMLText::TEXTBOX, 10, "username")),
	_password(new Engine::TextBox("password", SFMLImage::TEXTBOX, SFMLImage::TEXTBOX_SELECTED, SFMLImage::TEXTBOX_HOVER, SFMLText::TEXTBOX, 10, "password", '*')),
	_ip(new Engine::TextBox("ip", SFMLImage::TEXTBOX, SFMLImage::TEXTBOX_SELECTED, SFMLImage::TEXTBOX_HOVER, SFMLText::TEXTBOX, 16, "host")),
	_port(new Engine::TextBox("port", SFMLImage::TEXTBOX, SFMLImage::TEXTBOX_SELECTED, SFMLImage::TEXTBOX_HOVER, SFMLText::TEXTBOX, 4, "port")),
	_quit(new Engine::Button("quit", SFMLImage::BUTTON_QUIT, SFMLImage::BUTTON_CLICKED_QUIT, SFMLImage::BUTTON_HOVER_QUIT)),
	_settings(new Engine::Button("settings", SFMLImage::BUTTON_SETTINGS, SFMLImage::BUTTON_CLICKED_SETTINGS, SFMLImage::BUTTON_HOVER_SETTINGS, State::GAME)),
	_loading(new Engine::Background("loading", SFMLAnimation::LOADING))
{
}

ConnectionState::~ConnectionState()
{
}

//
// PRIVATE FUNCTIONS
//

void	ConnectionState::setInputText(Engine::TextBox* widget, size_t fontSize)
{

	widget->setTextSize(fontSize);
	widget->setTextPosition(15, 5);
	widget->setTextColor(Ultra::Color(208, 154, 58, 255));
}

//
// LIFE-CYCLE
//

void	ConnectionState::initialize()
{
	this->addChild(this->_background);
	this->addChild(this->_connection);
	this->addChild(this->_login);
	this->addChild(this->_password);
	this->addChild(this->_ip);
	this->addChild(this->_port);
	this->addChild(this->_quit);
	this->addChild(this->_settings);
	this->addChild(this->_loading);
	Widget::initialize();
	this->_loading->hide();
	this->addEventListener(Engine::Event::WINDOW, Engine::WindowEvent::CLOSED, &Engine::Callback::quit);
	this->addEventListener(Engine::Event::NETWORK, Ultra::Converter::numberToString(Message::AUTH_AVAILABLE),
		&Callback::Connection::checkAvailability);
	this->addEventListener(Engine::Event::NETWORK, Ultra::Converter::numberToString(Message::AUTH_ACCESS),
		&Callback::Connection::checkAccess);
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
		// Login textbox
		this->_login->setSize(width * 26 / 100, height * 8 / 100);
		this->_login->setPosition(width * 36 / 100, height * 36 / 100);
		ConnectionState::setInputText(this->_login, fontSize);
		// Password textbox
		this->_password->setSize(width * 26 / 100, height * 8 / 100);
		this->_password->setPosition(width * 36 / 100, height * 50 / 100);	
		ConnectionState::setInputText(this->_password, fontSize);
		// IP textbox
		this->_ip->setSize((size_t)((float)width * 17.5f / 100.0f), (size_t)((float)height * 8.0f / 100.0f));
		this->_ip->setPosition(width * 36 / 100, height * 66 / 100);	
		ConnectionState::setInputText(this->_ip, fontSize);
		// Port textbox
		this->_port->setSize(width * 8 / 100, height * 8 / 100);
		this->_port->setPosition(width * 54 / 100, height * 66 / 100);	
		ConnectionState::setInputText(this->_port, fontSize);
		// Quit button
		this->_quit->setSize(width * 9 / 100, height * 3 / 100);
		this->_quit->setPosition(width * 90 / 100, height * 1 / 100);
		this->_quit->removeEventListener(Engine::Event::MOUSE, Engine::MouseEvent::LEFT_CLICK);
		this->_quit->addEventListener(Engine::Event::MOUSE, Engine::MouseEvent::LEFT_CLICK, &Engine::Callback::Button::quit);
		// Settings button
		this->_settings->setSize(width * 9 / 100, height * 3 / 100);
		this->_settings->setPosition(width * 90 / 100, (int)((float)height * 4.5f / 100.0f));
		// Connection button
		this->_connection->setSize(width * 14 / 100, height * 5 / 100);
		this->_connection->setPosition(width * 42 / 100, height * 80 / 100);	
		this->_connection->lock();
		this->_connection->removeEventListener(Engine::Event::MOUSE, Engine::MouseEvent::LEFT_CLICK);
		this->_connection->addEventListener(Engine::Event::MOUSE, Engine::MouseEvent::LEFT_CLICK, &Callback::Connection::connectOnClick);
	}
	this->_networkModule = dynamic_cast<NetworkModule*>(Engine::Core::getInstance()->getModule(Engine::AModule::NETWORK));
}

void	ConnectionState::update()
{
	Widget::update();
	if (this->_login->getText() != "" && this->_password->getText() != "" 
		&& this->_ip->getText() != "" && this->_port->getText() != "")
		this->_connection->unlock();
	else
		this->_connection->lock();
}

void	ConnectionState::unload()
{
	this->removeEventListener(Engine::Event::WINDOW, Engine::WindowEvent::CLOSED);
	this->_loading->removeEventListener(Engine::Event::MOUSE, Engine::MouseEvent::MOUSE_MOVE);
	Widget::unload();
	this->removeAllChild();
}

void	ConnectionState::reset()
{
}

void	ConnectionState::reload()
{
	// to do set text
}

//
// PUBLIC FUNCTIONS
//

void	ConnectionState::connect()
{
	this->_loading->show();
	this->_login->lock();
	this->_password->lock();
	this->_ip->lock();
	this->_port->lock();
	Ultra::ScopeLock lock(Engine::Core::getInstance()->access(Engine::AModule::NETWORK));
	if (this->_networkModule->isStarted())
		this->_networkModule->stop();
	this->_networkModule->setHost(this->_ip->getText());
	this->_networkModule->setPort(Ultra::Value(this->_port->getText()).to<std::string, unsigned short>());
	if (this->_networkModule->start())
		this->_networkModule->addMessage(new TCPPacket(new Message(Message::AUTH_AVAILABLE), NetworkModule::AUTH), ISocket::TCP);
	else
		this->displayError("Host or port incorrect !");
}

void	ConnectionState::login()
{
	Message *msg = new Message(Message::AUTH_LOGIN);
	MD5encode md5;

	Ultra::IMutex *mutex = Engine::Core::getInstance()->access(Engine::AModule::DATA);
	
	mutex->lock();
	DataModule *dm = dynamic_cast<DataModule*>(Engine::Core::getInstance()->getModule(Engine::AModule::DATA));
	dm->setAttr("login", Ultra::Value(std::string(this->_login->getText())));
	mutex->unlock();

	msg->setAttr("login", Ultra::Value(std::string(this->_login->getText())));
	msg->setAttr("password", Ultra::Value(md5.encode(this->_password->getText())));
	Ultra::ScopeLock lock(Engine::Core::getInstance()->access(Engine::AModule::NETWORK));
	this->_networkModule->addMessage(new TCPPacket(msg, NetworkModule::AUTH), ISocket::TCP);
}

void	ConnectionState::play()
{
	this->_loading->hide();
	this->_login->unlock();
	this->_password->unlock();
	this->_ip->unlock();
	this->_port->unlock();
	this->_connection->active();
}

void	ConnectionState::displayError(std::string const &error)
{
	Ultra::IMutex* mutex = Engine::Core::getInstance()->access(Engine::AModule::NETWORK);
	mutex->lock();
	if (this->_networkModule->isStarted())
	{
		NetworkModule* networkModule = dynamic_cast<NetworkModule*>(Engine::Core::getInstance()->getModule(Engine::AModule::NETWORK));
		networkModule->stop();
	}
	mutex->unlock();
	this->_loading->hide();
	this->_login->unlock();
	this->_password->unlock();
	this->_ip->unlock();
	this->_port->unlock();
	std::cerr << error << std::endl;
}

