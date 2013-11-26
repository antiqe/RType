#ifndef _SFMLINPUT_H_
# define _SFMLINPUT_H_

#include <list>
#include <SFML/Graphics.hpp>

#include "IInput.hpp"
#include "Event.hpp"

class SFMLInput : public Engine::IInput<sf::Event>
{
private:
	typedef bool			(SFMLInput::*IsFunction)(sf::Event const&) const;
	typedef Engine::Event*	(SFMLInput::*CreateFunction)(sf::Event const&) const;

	SFMLInput::IsFunction		_isEvent[3];
	SFMLInput::CreateFunction	_createEvent[3];
	SFMLInput::IsFunction		_isMouseEvent[3];
	SFMLInput::CreateFunction	_createMouseEvent[3];

	bool			isEvent(int const table[], int len, int type) const;
	bool			isMouseMoveEvent(sf::Event const& e) const;
	bool			isMouseWheelEvent(sf::Event const& e) const;
	bool			isMouseClickEvent(sf::Event const& e) const;
	Engine::Event*	createKeyboardEvent(sf::Event const& e) const;
	Engine::Event*	createMouseEvent(sf::Event const& e) const;
	Engine::Event*	createMouseMoveEvent(sf::Event const& e) const;
	Engine::Event*	createMouseWheelEvent(sf::Event const& e) const;
	Engine::Event*	createMouseClickEvent(sf::Event const& e) const;
	Engine::Event*	createWindowEvent(sf::Event const& e) const;
public:
	SFMLInput();
	~SFMLInput();

	Engine::Event*	createEvent(sf::Event const& e) const;
	bool			isKeyboardEvent(sf::Event const& e) const;
	bool			isMouseEvent(sf::Event const& e) const;
	bool			isWindowEvent(sf::Event const& e) const;
};

#endif