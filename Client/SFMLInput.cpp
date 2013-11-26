#include <algorithm>
#include <string>

#include "SFMLInput.hpp"
#include "KeyboardEvent.hpp"
#include "MouseEvent.hpp"
#include "WindowEvent.hpp"

SFMLInput::SFMLInput()
{
	this->_isEvent[0] = &SFMLInput::isKeyboardEvent;
	this->_isEvent[1] = &SFMLInput::isMouseEvent;
	this->_isEvent[2] = &SFMLInput::isWindowEvent;
	this->_createEvent[0] = &SFMLInput::createKeyboardEvent;
	this->_createEvent[1] = &SFMLInput::createMouseEvent;
	this->_createEvent[2] = &SFMLInput::createWindowEvent;
	this->_isMouseEvent[0] = &SFMLInput::isMouseMoveEvent;
	this->_isMouseEvent[1] = &SFMLInput::isMouseWheelEvent;
	this->_isMouseEvent[2] = &SFMLInput::isMouseClickEvent;
	this->_createMouseEvent[0] = &SFMLInput::createMouseMoveEvent;
	this->_createMouseEvent[1] = &SFMLInput::createMouseWheelEvent;
	this->_createMouseEvent[2] = &SFMLInput::createMouseClickEvent;
}

SFMLInput::~SFMLInput()
{

}

Engine::Event*	SFMLInput::createEvent(sf::Event const& e) const
{
	for (int i = 0; i < 3; ++i)
		if ((this->*_isEvent[i])(e))
			return ((this->*_createEvent[i])(e));
	return (0);
}

bool	SFMLInput::isEvent(int const table[], int len, int type) const
{
	const std::list<int>	list(table, table + (len / sizeof(int)));

	return (std::find(list.begin(), list.end(), type) != list.end());
}

bool	SFMLInput::isKeyboardEvent(sf::Event const& e) const
{
	const int				table[] = {
		sf::Event::KeyReleased,
		sf::Event::KeyPressed
	};

	return (this->isEvent(table, sizeof(table), e.type));
}

bool	SFMLInput::isMouseEvent(sf::Event const& e) const
{
	const int				table[] = {
		sf::Event::MouseButtonPressed,
		sf::Event::MouseButtonReleased,
		sf::Event::MouseMoved,
		sf::Event::MouseWheelMoved
	};

	return (this->isEvent(table, sizeof(table), e.type));
}

bool	SFMLInput::isWindowEvent(sf::Event const& e) const
{
	const int				table[] = {
		sf::Event::Closed,
		sf::Event::LostFocus,
		sf::Event::GainedFocus
	};

	return (this->isEvent(table, sizeof(table), e.type));
}

Engine::Event*	SFMLInput::createKeyboardEvent(sf::Event const& e) const
{
	std::string	type = e.type == sf::Event::KeyPressed ?
		Engine::KeyboardEvent::KEY_PRESSED : Engine::KeyboardEvent::KEY_RELEASED;

	return (new Engine::KeyboardEvent(type, e.key.code, e.key.control, e.key.alt, e.key.shift));
}

bool	SFMLInput::isMouseMoveEvent(sf::Event const& e) const
{
	return (e.type == sf::Event::MouseMoved);
}

bool	SFMLInput::isMouseWheelEvent(sf::Event const& e) const
{
	return (e.type == sf::Event::MouseWheelMoved);
}

bool	SFMLInput::isMouseClickEvent(sf::Event const& e) const
{
	return (e.type == sf::Event::MouseButtonPressed || e.type == sf::Event::MouseButtonReleased);
}

Engine::Event*	SFMLInput::createMouseMoveEvent(sf::Event const& e) const
{
	return (new Engine::MouseEvent(Engine::MouseEvent::MOUSE_MOVE, e.mouseMove.x, e.mouseMove.y));
}

Engine::Event*	SFMLInput::createMouseWheelEvent(sf::Event const& e) const
{
	return (new Engine::MouseEvent(Engine::MouseEvent::MOUSE_WHEEL, e.mouseWheel.x, e.mouseWheel.y, e.mouseWheel.delta));
}

Engine::Event*	SFMLInput::createMouseClickEvent(sf::Event const& e) const
{
	std::string const	type = e.mouseButton.button == sf::Mouse::Right ?
		Engine::MouseEvent::RIGHT_CLICK : (e.mouseButton.button == sf::Mouse::Middle ?
		Engine::MouseEvent::MIDDLE_CLICK : Engine::MouseEvent::LEFT_CLICK);

	return (new Engine::MouseEvent(type, e.mouseButton.x, e.mouseButton.y, e.type == sf::Event::MouseButtonPressed));
}

Engine::Event*	SFMLInput::createMouseEvent(sf::Event const& e) const
{
	for (int i = 0; i < 3; ++i)
		if ((this->*_isMouseEvent[i])(e))
			return ((this->*_createMouseEvent[i])(e));
	return (0);
}

Engine::Event*	SFMLInput::createWindowEvent(sf::Event const& e) const
{
	std::string	type = e.type == sf::Event::Closed ?
		Engine::WindowEvent::CLOSED : (e.type == sf::Event::LostFocus ?
		Engine::WindowEvent::LOST_FOCUS : Engine::WindowEvent::GAINED_FOCUS);

	return (new Engine::WindowEvent(type));
}