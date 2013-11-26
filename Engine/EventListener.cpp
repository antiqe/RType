#include "EventListener.hpp"

namespace Engine
{
	EventListener::Compare::Compare(std::string const& name, std::string const& type)
		: _name(name), _type(type)
	{

	}

	EventListener::Compare::~Compare()
	{

	}

	bool	EventListener::Compare::operator()(EventListener const& el) const
	{
		return (el.getName() == this->_name && (this->_type.empty() || el.getType() == this->_type));
	}


	EventListener::Functor::Functor(std::string const& name, std::string const& type, Widget* widget, Event* event)
		: _name(name), _type(type), _widget(widget), _event(event)
	{

	}

	EventListener::Functor::~Functor()
	{

	}

	void	EventListener::Functor::operator()(EventListener const& el)
	{
		if (el.getName() == this->_name && el.getType() == this->_type)
			el.execute(this->_widget, this->_event);
	}

	EventListener::EventListener(std::string const& name, Callback::EventFunction callback, int priority)
		: _name(name), _type(""), _callback(callback), _priority(priority)
	{

	}

	EventListener::EventListener(std::string const& name, std::string const& type, Callback::EventFunction callback, int priority)
		: _name(name), _type(type), _callback(callback), _priority(priority)
	{

	}

	EventListener::~EventListener()
	{

	}

	std::string const&		EventListener::getName() const
	{
		return (this->_name);
	}

	std::string const&		EventListener::getType() const
	{
		return (this->_type);
	}

	int				EventListener::getPriority() const
	{
		return (this->_priority);
	}

	Callback::EventFunction		EventListener::getCallback() const
	{
		return (this->_callback);
	}

	bool	EventListener::operator<(EventListener const& el) const
	{
		return (this->getPriority() < el.getPriority());
	}

	void	EventListener::execute(Widget* widget, Event* event) const
	{
		this->_callback(widget, event);
	}
}
