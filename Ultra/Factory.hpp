#ifndef _FACTORY_H_
# define _FACTORY_H_

#include <string>
#include <map>

#include "IPrototype.hpp"

namespace Ultra
{
	template <typename T, typename U = std::string>
	class Factory
	{
	protected:
		std::map<U, T>						_objects;
	public:
		Factory() {}

		virtual ~Factory() {}

		void	learn(U const& key, T object)
		{
			if (this->_objects.find(key) == this->_objects.end())
				this->_objects.insert(std::pair<U, T>(key, object));
		}

		void	forget(U const& key)
		{
			if (this->_objects.find(key) != this->_objects.end())
				this->_objects.erase(key);
		}

		T*		create(U const& key) const
		{
			typename std::map<U, T>::const_iterator it = this->_objects.find(key);

			if (it != this->_objects.end())
				return (it->second.clone());
			return (0);
		}

		std::map<U, T> const&		getAllObject() const
		{
			return (this->_objects);
		}
	};
}

#endif