#include "GameState.hpp"
#include "State.hpp"
#include "Event.hpp"
#include "MouseEvent.hpp"
#include "WindowEvent.hpp"
#include "Core.hpp"
#include "SFMLImage.hpp"
#include "SFMLText.hpp"

GameState::GameState()
	: AState(State::CONNECTION),
	_dataModule(0),
	_background (new Engine::HParallax("background", SFMLImage::BACKGROUND, 0.25f)),
	_terre(new Engine::HParallax("terre", SFMLImage::TERRE, 0.8f))
{

}

GameState::~GameState()
{

}

void	GameState::initialize()
{
	this->addChild(this->_background);
	this->addChild(this->_terre);
	Widget::initialize();
	this->addEventListener(Engine::Event::WINDOW, Engine::WindowEvent::CLOSED, &Engine::Callback::quit);
	if ((this->_dataModule = dynamic_cast<DataModule*>(Engine::Core::getInstance()->getModule(Engine::AModule::DATA))))
	{
		size_t	width = this->_dataModule->getAttr<size_t>("winWidth");
		size_t	height = this->_dataModule->getAttr<size_t>("winHeight");
		// Background
		this->_background->setSize(width, height);
		this->_background->setPosition(0, 0);
		// Terre
		this->_terre->setSize(width * 2, height * 2);
		this->_terre->setPosition(-(int)width, 0);
	}
}

void	GameState::update()
{
	Widget::update();
}

void	GameState::unload()
{
	this->removeEventListener(Engine::Event::WINDOW, Engine::WindowEvent::CLOSED);
	Widget::unload();
	this->removeAllChild();
}

void	GameState::reset()
{

}

void	GameState::reload()
{

}