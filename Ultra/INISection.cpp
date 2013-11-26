#include "INISection.hpp"

namespace Ultra
{
	INISection::INISection(std::string const &name)
		: _name(name)
	{
	}

	std::string INISection::getName() const
	{
		return (this->_name);
	}

	void INISection::setField(std::string const &name, Ultra::Value const &val)
	{
		this->_fields[name] = val;
	}

	std::map<std::string, Ultra::Value> INISection::getAllField() const
	{
		return (this->_fields);
	}
}