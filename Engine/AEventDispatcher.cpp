#include <iterator>
#include <iterator>
#include <algorithm>
#include <functional>
#include <iomanip>

#include "AEventDispatcher.hpp"

namespace Engine
{
	AEventDispatcher::AEventDispatcher()
	{

	}

	AEventDispatcher::~AEventDispatcher()
	{

	}

	void	AEventDispatcher::addEventListener(std::string const& name, std::string const& type, Callback::EventFunction callback, int priority)
	{
		this->_els.push_front(EventListener(name, type, callback, priority));
		this->_els.sort();
	}

	void	AEventDispatcher::addEventListener(std::string const& name, Callback::EventFunction callback, int priority)
	{
		this->_els.push_front(EventListener(name, callback, priority));
		this->_els.sort();
	}

	void	AEventDispatcher::removeEventListener(std::string const& name, std::string const& type)
	{
		std::list<EventListener>::iterator it;

		it = std::find_if(this->_els.begin(), this->_els.end(),	EventListener::Compare(name, type));
		if (it != this->_els.end())
			this->_els.erase(it);
	}

	void	AEventDispatcher::removeEventListener(std::string const& name)
	{
		std::list<EventListener>::iterator it;

		it = std::find_if(this->_els.begin(), this->_els.end(), EventListener::Compare(name));
		if (it != this->_els.end())
			this->_els.erase(it);
	}

	void	AEventDispatcher::removeAllEventListener(std::string const& name, std::string const& type)
	{
		this->_els.remove_if(EventListener::Compare(name, type));
	}

	void	AEventDispatcher::removeAllEventListener(std::string const& name)
	{
		this->_els.remove_if(EventListener::Compare(name));
	}

	bool	AEventDispatcher::hasEventListener(std::string const& name, std::string const& type) const
	{
		std::list<EventListener>::const_iterator it;

		it = std::find_if(this->_els.begin(), this->_els.end(), EventListener::Compare(name, type));
		return (it != this->_els.end());
	}

	bool	AEventDispatcher::hasEventListener(std::string const& name) const
	{
		std::list<EventListener>::const_iterator it;

		it = std::find_if(this->_els.begin(), this->_els.end(), EventListener::Compare(name));
		return (it != this->_els.end());
	}
}