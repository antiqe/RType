#ifndef _ATTR_H_
# define _ATTR_H_

#include <map>
#include <string>

#include "Value.hpp"
#include "Exception.hpp"

namespace Ultra
{
	class Attr
	{
	protected:
		std::map<std::string, Ultra::Value>	_attr;
	public:
		class Exception : public Ultra::Exception
		{
		public:
			Exception(std::string const& message) throw();
			~Exception() throw();
		};
		Attr();
		Attr(Attr const& cpy);
		virtual ~Attr();
		Attr&	operator=(Attr const& cpy);

		void	setAttr(std::string const& name, Ultra::Value const& value);
		bool	delAttr(std::string const& name);
		std::map<std::string, Ultra::Value> getAllAttrs() const;
		void	clearAttrs();

		template <typename T>
		T const getAttr(std::string const &name) const
		{
			std::map<std::string, Ultra::Value>::const_iterator	it = this->_attr.find(name);

			if (it == this->_attr.end())
			{
				std::string	message = "Attribute '";
				message += name + "' undeclared";
				//throw Ultra::Exception(message);
			}
			return (it->second.as<T>());
		}
	};
}

#endif
