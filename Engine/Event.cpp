#include "Event.hpp"

namespace Engine
{
	std::string const	Event::KEYBOARD = "keyboard";
	std::string const	Event::MOUSE = "mouse";
	std::string const	Event::WINDOW = "window";
	std::string const   Event::NETWORK = "network";

	Event::Event(std::string const& name, std::string const& type)
		: Ultra::Attr(), _name(name), _type(type)
	{

	}

	Event::Event(Event const& cpy)
		: Attr(cpy), _name(cpy._name), _type(cpy._type)
	{

	}

	Event::~Event()
	{

	}

	Event&	Event::operator=(Event const& cpy)
	{
		if (this != &cpy)
		{
			this->_name = cpy._name;
			this->_type = cpy._type;
		}
		return (*this);
	}

	void	Event::setType(std::string const& type)
	{
		this->_type = type;
	}

	void	Event::setName(std::string const& name)
	{
		this->_name = name;
	}

	std::string const&	Event::getName() const
	{
		return (this->_name);
	}

	std::string const&	Event::getType() const
	{
		return (this->_type);
	}
}