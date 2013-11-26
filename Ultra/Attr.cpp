#include "Attr.hpp"

namespace Ultra
{
	Attr::Attr()
		: _attr(std::map<std::string, Ultra::Value>())
	{

	}

	Attr::Attr(Attr const& cpy)
		: _attr(cpy._attr)
	{

	}

	Attr::~Attr()
	{

	}

	Attr&	Attr::operator=(Attr const& cpy)
	{
		if (this != &cpy)
			this->_attr = cpy._attr;
		return (*this);
	}

	void	Attr::setAttr(std::string const& name, Ultra::Value const& value)
	{
		this->_attr[name] = value;
	}

	bool	Attr::delAttr(std::string const& name)
	{
		std::map<std::string, Ultra::Value>::iterator	it = this->_attr.find(name);

		if (it == this->_attr.end())
			return (false);
		this->_attr.erase(it);
		return (true);
	}

	std::map<std::string, Ultra::Value> Attr::getAllAttrs() const
	{
		return this->_attr;
	}

	void	Attr::clearAttrs()
	{
	  this->_attr = std::map<std::string, Ultra::Value>();
	}
  
	Attr::Exception::Exception(std::string const& message) throw()
	: Ultra::Exception("Attr", message)
	{

	}

	Attr::Exception::~Exception() throw()
	{

	}
}
