#include "Value.hpp"

namespace Ultra
{
	Value::Value() : _type(Value::UNKNOWN) {}
	Value::Value(char value) : _type(Value::CHAR), _char(value) {}
	Value::Value(unsigned char value) : _type(Value::UCHAR), _uchar(value) {}
	Value::Value(short value) : _type(Value::SHORT), _short(value) {}
	Value::Value(unsigned short value) : _type(Value::USHORT), _ushort(value) {}
	Value::Value(int value) : _type(Value::INT), _int(value) {}
	Value::Value(unsigned int value) : _type(Value::UINT), _uint(value) {}
	Value::Value(long value) : _type(Value::LONG), _long(value) {}
	Value::Value(unsigned long value) : _type(Value::ULONG), _ulong(value) {}
	Value::Value(float value) : _type(Value::FLOAT), _float(value) {}
	Value::Value(double value) : _type(Value::DOUBLE), _double(value) {}
	Value::Value(std::string value) : _type(Value::STRING), _string(value) {}
	Value::Value(bool value) : _type(Value::BOOL), _bool(value) {}

	Value::Value(Value const& cpy)
		: _type(cpy._type),
		_char(cpy._char),
		_uchar(cpy._uchar),
		_short(cpy._short),
		_ushort(cpy._ushort),
		_int(cpy._int),
		_uint(cpy._uint),
		_long(cpy._long),
		_ulong(cpy._ulong),
		_float(cpy._float),
		_double(cpy._double),
		_string(cpy._string),
		_bool(cpy._bool)
	{

	}

	Value&	Value::operator=(Value const& cpy)
	{
		if (this != &cpy)
		{
			this->_type = cpy._type;
			this->_char = cpy._char;
			this->_uchar = cpy._uchar;
			this->_short = cpy._short;
			this->_ushort = cpy._ushort;
			this->_int = cpy._int;
			this->_uint = cpy._uint;
			this->_long = cpy._long;
			this->_ulong = cpy._ulong;
			this->_float = cpy._float;
			this->_double = cpy._double;
			this->_string = cpy._string;
			this->_bool = cpy._bool;
		}
		return (*this);
	}

	Value::Type	Value::getType() const
	{
		return (this->_type);
	}

	void	Value::integrity(Value::Type const& type) const
	{
		const std::string	dict[TYPESIZE] = {
			"char", "unsigned char", "short", "unsigned short",
			"int", "unsigned int", "long", "unsigned long",
			"float", "double", "string", "bool", "undefined type"
		};

		if (this->_type != type)
		{
			std::string	message = "Cannot convert '";
			message += dict[this->_type] + "' to '";
			message += dict[type] + "'";
			throw Value::Exception(message);
		}
	}

	template <>
	char Value::as<char>() const
	{
	  this->integrity(Value::CHAR);

	  return (this->_char);
	}

	template <>
	unsigned char	Value::as<unsigned char>() const
	{
		this->integrity(Value::UCHAR);

		return (this->_uchar);
	}

	template <>
	short 	Value::as<short>() const
	{
		this->integrity(Value::SHORT);

		return (this->_short);
	}

	template <>
	unsigned short 	Value::as<unsigned short>() const
	{
		this->integrity(Value::USHORT);

		return (this->_ushort);
	}

	template <>
	int 	Value::as<int>() const
	{
		this->integrity(Value::INT);

		return (this->_int);
	}

	template <>
	unsigned int 	Value::as<unsigned int>() const
	{
		this->integrity(Value::UINT);

		return (this->_uint);
	}

	template <>
	long	Value::as<long>() const
	{
		this->integrity(Value::LONG);

		return (this->_long);
	}

	template <>
	unsigned long	Value::as<unsigned long>() const
	{
		this->integrity(Value::ULONG);

		return (this->_ulong);
	}

	template <>
	float 	Value::as<float>() const
	{
		this->integrity(Value::FLOAT);

		return (this->_float);
	}

	template <>
	double 	Value::as<double>() const
	{
		this->integrity(Value::DOUBLE);

		return (this->_double);
	}

	template <>
	std::string 	Value::as<std::string>() const
	{
		this->integrity(Value::STRING);

		return (this->_string);
	}

	template <>
	bool 	Value::as<bool>() const
	{
		this->integrity(Value::BOOL);

		return (this->_bool);
	}

	template <>
	std::string				Value::to<char, std::string>() const
	{
		return (Ultra::Converter::numberToString(this->as<char>()));
	}

	template <>
	std::string				Value::to<unsigned char, std::string>() const
	{
		return (Ultra::Converter::numberToString(this->as<unsigned char>()));	
	}

	template <>
	std::string				Value::to<short, std::string>() const
	{
		return (Ultra::Converter::numberToString(this->as<short>()));	
	}

	template <>
	std::string				Value::to<unsigned short, std::string>() const
	{
		return (Ultra::Converter::numberToString(this->as<unsigned short>()));	
	}

	template <>
	std::string				Value::to<int, std::string>() const
	{
		return (Ultra::Converter::numberToString(this->as<int>()));	
	}

	template <>
	std::string				Value::to<unsigned int, std::string>() const
	{
		return (Ultra::Converter::numberToString(this->as<unsigned int>()));	
	}

	template <>
	std::string				Value::to<long, std::string>() const
	{
		return (Ultra::Converter::numberToString(this->as<long>()));	
	}

	template <> 
	std::string				Value::to<unsigned long, std::string>() const
	{
		return (Ultra::Converter::numberToString(this->as<unsigned long>()));	
	}

	template <>
	std::string				Value::to<float, std::string>() const
	{
		return (Ultra::Converter::numberToString(this->as<float>()));	
	}

	template <>
	std::string				Value::to<double, std::string>() const
	{
		return (Ultra::Converter::numberToString(this->as<double>()));	
	}

	template <>
	std::string				Value::to<bool, std::string>() const
	{
		return (Ultra::Converter::numberToString(this->as<bool>()));	
	}

	template <>
	char					Value::to<std::string, char>() const
	{
		return (Ultra::Converter::stringToNumber<char>(this->as<std::string>()));
	}

	template <>
	unsigned char			Value::to<std::string, unsigned char>() const
	{
		return (Ultra::Converter::stringToNumber<unsigned char>(this->as<std::string>()));
	}

	template <>
	short					Value::to<std::string, short>() const
	{
		return (Ultra::Converter::stringToNumber<short>(this->as<std::string>()));
	}

	template <>
	unsigned short			Value::to<std::string, unsigned short>() const
	{
		return (Ultra::Converter::stringToNumber<unsigned short>(this->as<std::string>()));
	}

	template <>
	int						Value::to<std::string, int>() const
	{
		return (Ultra::Converter::stringToNumber<int>(this->as<std::string>()));
	}

	template <>
	unsigned int			Value::to<std::string, unsigned int>() const
	{
		return (Ultra::Converter::stringToNumber<unsigned int>(this->as<std::string>()));
	}

	template <>
	long					Value::to<std::string, long>() const
	{
		return (Ultra::Converter::stringToNumber<long>(this->as<std::string>()));
	}

	template <>
	unsigned long			Value::to<std::string, unsigned long>() const
	{
		return (Ultra::Converter::stringToNumber<unsigned long>(this->as<std::string>()));
	}

	template <>
	float					Value::to<std::string, float>() const
	{
		return (Ultra::Converter::stringToNumber<float>(this->as<std::string>()));
	}

	template <>
	double					Value::to<std::string, double>() const
	{
		return (Ultra::Converter::stringToNumber<double>(this->as<std::string>()));
	}

	template <>
	bool					Value::to<std::string, bool>() const
	{
		return (Ultra::Converter::stringToNumber<bool>(this->as<std::string>()));
	}

	Value::Exception::Exception(std::string const& message, Exception::Type const& type) throw()
		: Ultra::Exception("Value", message, type)
	{

	}
}
