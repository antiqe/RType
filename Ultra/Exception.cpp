#include "Exception.hpp"

namespace Ultra
{
	Exception::Exception(std::string const& module, std::string const& message, Exception::Type const& type) throw()
		: _type(type), _module(module), _message(message)
	{

	}

	Exception::Type const&	Exception::which() const throw()
	{
		return (this->_type);
	}

	const char*	Exception::what() const throw()
	{
		return (this->_message.c_str());
	}

	const char*	Exception::who() const throw()
	{
		return (this->_module.c_str());
	}
}

std::ostream&	operator<<(std::ostream& stream, Ultra::Exception const& e)
{
	const std::string	dict[Ultra::Exception::TYPESIZE] = {
		"Error", "Warning", "Notice"
	};

	stream << e.who() << " : " << dict[e.which()] << " : " << e.what();
	return (stream);
}
