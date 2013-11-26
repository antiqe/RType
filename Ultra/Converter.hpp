#ifndef _CONVERTER_H_
# define _CONVERTER_H_

#include <sstream>
#include <string>

namespace Ultra
{
	namespace Converter
	{
		template <typename T>
		T	stringToNumber(std::string const& str)
		{
			std::stringstream	ss(str);
			T	number = static_cast<T>(0);

			ss >> number;
			return (number);
		}

		template <typename T>
		std::string	numberToString(T number)
		{
			std::stringstream ss;

			ss << number;
			return (ss.str());
		}

		template <typename T>
		inline T abs(T nbr)
		{
			return (nbr > 0 ? nbr : -nbr);
		}
	}
}

#endif /* _CONVERTER_H_ */
