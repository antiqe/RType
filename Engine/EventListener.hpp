#ifndef _EVENTLISTENER_H_
# define _EVENTLISTENER_H_

#include <sys/types.h>
#include <string>

#include "Event.hpp"
#include "Callback.hpp"
#include "ICompare.hpp"
#include "IFunctor.hpp"

namespace Engine
{
	class Widget;

	class EventListener
	{
	private:
		std::string				_name;
		std::string				_type;
		Callback::EventFunction	_callback;
		int						_priority;
	public:
		class Compare : public Ultra::ICompare<EventListener>
		{
		private:
			std::string _name;
			std::string	_type;
		public:
			Compare(std::string const& name, std::string const& type = "");
			~Compare();

			bool	operator()(EventListener const& el) const;
		};

		class Functor : public Ultra::IFunctor<EventListener>
		{
		private:
			std::string _name;
			std::string	_type;
			Widget*		_widget;
			Event*		_event;
		public:
			Functor(std::string const& name, std::string const& type, Widget* widget, Event* event);
			~Functor();

			void	operator()(EventListener const& el);
		};

		EventListener(std::string const& name, std::string const& type, Callback::EventFunction callback, int priority = 0);
		EventListener(std::string const& name, Callback::EventFunction callback, int priority = 0);
		~EventListener();

		std::string const&			getName() const;
		std::string const&			getType() const;
		Callback::EventFunction		getCallback() const;
		int							getPriority() const;

		bool	operator<(EventListener const& el) const;

		void	execute(Widget* widget, Event* event) const;
	};
}

#endif