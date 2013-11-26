#ifndef _EVENT_H_
# define _EVENT_H_

#include <string>

#include "Attr.hpp"

namespace Engine
{
	class Event : public Ultra::Attr
	{
	protected:
		std::string	_name;
		std::string	_type;
	public:
		explicit Event(std::string const& name, std::string const& type);
		Event(Event const& cpy);
		Event&	operator=(Event const& cpy);
		virtual ~Event();

		void			setType(std::string const& type);
		void			setName(std::string const& name);

		std::string const&	getType() const;
		std::string const&	getName() const;

		static std::string const	KEYBOARD;
		static std::string const	MOUSE;
		static std::string const	WINDOW;
		static std::string const    NETWORK;
	};
}

#endif
