#ifndef __VALUE_HPP__
#define __VALUE_HPP__

#include <iostream>
#include <string>

#include "Exception.hpp"
#include "Converter.hpp"

namespace Ultra
{
	class Value
	{
	public:
		enum Type
		{
			CHAR = 0,
			UCHAR,
			SHORT,
			USHORT,
			INT,
			UINT,
			LONG,
			ULONG,
			FLOAT,
			DOUBLE,
			STRING,
			BOOL,
			UNKNOWN,
			TYPESIZE
		};
		class Exception : public Ultra::Exception
		{
		public:
			Exception(std::string const& message,
				Exception::Type const& type = Exception::FATAL) throw();
			virtual ~Exception() throw() {}
		};
	private:
		Value::Type		_type;
		char			_char;
		unsigned char	_uchar;
		short			_short;
		unsigned short	_ushort;
		int				_int;
		unsigned int	_uint;
		long			_long;
		unsigned long	_ulong;
		float			_float;
		double			_double;
		std::string		_string;
		bool			_bool;

		void	integrity(Value::Type const& type) const;
	public:
		Value();
		Value(char value);
		Value(unsigned char value);
		Value(short value);
		Value(unsigned short value);
		Value(int value);
		Value(unsigned int value);
		Value(long value);
		Value(unsigned long value);
		Value(float value);
		Value(double value);
		Value(std::string value);
		Value(bool value);
		Value(Value const& cpy);

		Value&		operator=(Value const& cpy);
		Value::Type	getType() const;

	  template <typename T>
		T 	as() const;

		template <typename T, typename U>
		U	to() const
		{
			return (static_cast<U>(this->as<T>()));
		}
	};

	template <> char 				Value::as<char>() const;
	template <> unsigned char 		Value::as<unsigned char>() const;
	template <> short 				Value::as<short>() const;
	template <> unsigned short 		Value::as<unsigned short>() const;
	template <> int 				Value::as<int>() const;
	template <> unsigned int 		Value::as<unsigned int>() const;
	template <> long 				Value::as<long>() const;
	template <> unsigned long		Value::as<unsigned long>() const;
	template <> float 				Value::as<float>() const;
	template <> double 				Value::as<double>() const;
	template <> std::string 		Value::as<std::string>() const;
	template <> bool 				Value::as<bool>() const;

	template <> std::string				Value::to<char, std::string>() const;
	template <> std::string				Value::to<unsigned char, std::string>() const;
	template <> std::string				Value::to<short, std::string>() const;
	template <> std::string				Value::to<unsigned short, std::string>() const;
	template <> std::string				Value::to<int, std::string>() const;
	template <> std::string				Value::to<unsigned int, std::string>() const;
	template <> std::string				Value::to<long, std::string>() const;
	template <> std::string				Value::to<unsigned long, std::string>() const;
	template <> std::string				Value::to<float, std::string>() const;
	template <> std::string				Value::to<double, std::string>() const;
	template <> std::string				Value::to<bool, std::string>() const;

	template <> char					Value::to<std::string, char>() const;
	template <> unsigned char			Value::to<std::string, unsigned char>() const;
	template <> short					Value::to<std::string, short>() const;
	template <> unsigned short			Value::to<std::string, unsigned short>() const;
	template <> int						Value::to<std::string, int>() const;
	template <> unsigned int			Value::to<std::string, unsigned int>() const;
	template <> long					Value::to<std::string, long>() const;
	template <> unsigned long			Value::to<std::string, unsigned long>() const;
	template <> float					Value::to<std::string, float>() const;
	template <> double					Value::to<std::string, double>() const;
	template <> bool					Value::to<std::string, bool>() const;
}

#endif