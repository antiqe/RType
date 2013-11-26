#ifndef _EXCEPTION_H_
# define _EXCEPTION_H_

#include <iostream>
#include <string>
#include <exception>

namespace Ultra
{
	class Exception : public std::exception
	{
	public:
		enum Type
		{
			FATAL = 0,
			WARNING,
			NOTICE,
			TYPESIZE
		};
	private:
		Exception::Type	_type;
		std::string		_module;
		std::string		_message;
	public:
		Exception(std::string const& module, std::string const& message, Exception::Type const& type = Exception::FATAL) throw();
		virtual ~Exception() throw() {}

		virtual Exception::Type const&	which() const throw();
		virtual const char*				what() const throw();
		virtual const char*				who() const throw();
	};
}

std::ostream&	operator<<(std::ostream& stream, Ultra::Exception const& e);

#endif /* _EXCEPTION_H_ */
