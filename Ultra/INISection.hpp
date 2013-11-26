#ifndef __INISECTION_H__
#define __INISECTION_H__

#include <map>
#include <string>

#include "Value.hpp"

namespace Ultra
{
	class INISection
	{
	private:
		std::string _name;
		std::map<std::string, Ultra::Value> _fields;
	public:
		INISection(std::string const &name);
		std::string getName() const;
		void setField(std::string const &name, Ultra::Value const &val);
		template <typename T>
		T getField(std::string const &field)
		{
			return (this->_fields[field].to<std::string, T>());
		}
		std::map<std::string, Ultra::Value> getAllField() const;
	};
};

#endif