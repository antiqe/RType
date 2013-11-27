#include "GameState.hpp"
#include "State.hpp"
#include "Event.hpp"
#include "MouseEvent.hpp"
#include "WindowEvent.hpp"
#include "Core.hpp"
#include "SFMLImage.hpp"
#include "GameCallback.hpp"
#include "SFMLText.hpp"

GameState::GameState()
	: AState(State::CONNECTION),
	_dataModule(0),
	_background (new Engine::HParallax("background", SFMLImage::BACKGROUND, 0.25f)),
	_terre(new Engine::HParallax("terre", SFMLImage::TERRE, 0.8f)),
	_logicTree(0)
{

}

GameState::~GameState()
{

}

#include "AVectorComponent.hpp"

void	GameState::initialize()
{
	this->addChild(this->_background);
	this->addChild(this->_terre);
	Widget::initialize();
	this->addEventListener(Engine::Event::WINDOW, Engine::WindowEvent::CLOSED, &Engine::Callback::quit);
	this->addEventListener(Engine::Event::NETWORK, Ultra::Converter::numberToString(Message::GAME_OBJ_CREATE), &Callback::Game::logicNetwork);
	this->addEventListener(Engine::Event::NETWORK, Ultra::Converter::numberToString(Message::GAME_OBJECT_INFO), &Callback::Game::logicNetwork);
	this->addEventListener(Engine::Event::KEYBOARD, Engine::KeyboardEvent::KEY_PRESSED, &Callback::Game::logicInput);
	this->addEventListener(Engine::Event::KEYBOARD, Engine::KeyboardEvent::KEY_RELEASED, &Callback::Game::logicInput);
	if ((this->_dataModule = dynamic_cast<DataModule*>(Engine::Core::getInstance()->getModule(Engine::AModule::DATA))))
	{
		this->resize(this->_dataModule->getAttr<size_t>("winWidth"), this->_dataModule->getAttr<size_t>("winHeight"));
		this->_logicTree = new Engine::LogicTree(Engine::Core::gameObjectFactory,
			this->_dataModule->getAttr<short>("mapUnit"),
			this->_dataModule->getAttr<size_t>("mapWidth"),
			this->_dataModule->getAttr<size_t>("mapHeight"));
	}
	this->addChild(this->_logicTree);
	this->_logicTree->initialize();
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
	this->_keyMap.clear();
	this->_vectorMap.clear();
	Ultra::ScopeLock	lock(Engine::Core::getInstance()->access(Engine::AModule::DATA));
	this->_keyMap[this->_dataModule->getAttr<int>("upKey")] = Ultra::Vector2D<float>(0.0f, -1.0f); 
	this->_keyMap[this->_dataModule->getAttr<int>("downKey")] = Ultra::Vector2D<float>(0.0f, 1.0f); 
	this->_keyMap[this->_dataModule->getAttr<int>("leftKey")] = Ultra::Vector2D<float>(-1.0f, 0.0f); 
	this->_keyMap[this->_dataModule->getAttr<int>("rightKey")] = Ultra::Vector2D<float>(1.0f, 0.0f);
	this->_keyMap[this->_dataModule->getAttr<int>("shootKey")] = Ultra::Vector2D<float>(0.0f, 0.0f);
	this->_vectorMap[this->_dataModule->getAttr<int>("upKey")] = false; 
	this->_vectorMap[this->_dataModule->getAttr<int>("downKey")] = false;
	this->_vectorMap[this->_dataModule->getAttr<int>("leftKey")] = false;
	this->_vectorMap[this->_dataModule->getAttr<int>("rightKey")] = false;
	this->_vectorMap[this->_dataModule->getAttr<int>("shootKey")] = false;
	Engine::GameObject*	tmp = Engine::Core::gameObjectFactory->create(this->_dataModule->getAttr<std::string>("tmp"));
	this->_logicTree->addObject(tmp);
	this->_logicTree->setTarget(tmp->getID());
}

void	GameState::reload()
{

}

void	GameState::resize(size_t width, size_t height)
{
	if (this->_dataModule)
	{
		// Background
		this->_background->setSize(width, height);
		this->_background->setPosition(0, 0);
		// Terre
		this->_terre->setSize(width * 2, height * 2);
		this->_terre->setPosition(-(int)width, 0);
	}
}

void	GameState::enableAction(Engine::KeyboardEvent* event)
{
	std::map<int, bool>::iterator	it = this->_vectorMap.find((int)event->getKeycode());

	if (it != this->_vectorMap.end())
	{
		Ultra::ScopeLock	lock(Engine::Core::getInstance()->access(Engine::AModule::DATA));
		if (this->_dataModule->getAttr<int>("shootKey") == it->first)
			this->_logicTree->preshoot();
		else
		{
			this->_vectorMap[it->first] = true;
			this->move();
		}
	}
}

void	GameState::move()
{
	Ultra::Vector2D<float>	vector(0.0f, 0.0f);
	int	i = 0;
	for (std::map<int, Ultra::Vector2D<float> >::iterator it = this->_keyMap.begin(); it != this->_keyMap.end(); ++it)
	{
		if (this->_vectorMap[it->first])
		{
			++i;
			vector.setX((vector.getX() +  this->_keyMap[it->first].getX()) / i);
			vector.setY((vector.getY() +  this->_keyMap[it->first].getY()) / i);
		}
	}
	this->_logicTree->move(vector);
}


void	GameState::disableAction(Engine::KeyboardEvent* event)
{
	std::map<int, bool>::iterator	it = this->_vectorMap.find((int)event->getKeycode());

	if (it != this->_vectorMap.end())
	{
		Ultra::ScopeLock	lock(Engine::Core::getInstance()->access(Engine::AModule::DATA));
		if (this->_dataModule->getAttr<int>("shootKey") == it->first)
			this->_logicTree->shoot();
		else
		{
			this->_vectorMap[it->first] = false;
			this->move();
		}
	}
}

void	GameState::maj(Engine::NetworkEvent* network)
{
	std::cout << "OULLALA JE RECOIS DES EVENTS NETWORKS" << std::endl;
}