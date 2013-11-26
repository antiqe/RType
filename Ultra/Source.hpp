#ifndef _SOURCE_H_
# define _SOURCE_H_

#include <functional>
#include <string>
#include <map>

namespace Ultra
{
	template <typename T, typename U = std::string>
	class Source
	{
	private:
		bool	_initialize;

		void	check()
		{
			if (!this->_initialize)
			{
				typename std::map<U, std::pair<T*, bool> >::iterator it = this->_objects.begin();
				this->_initialize = true;
				for (; it != this->_objects.end(); ++it)
					if (!it->second.second)
					{
						this->_initialize = false;
						break;
					}
			}
		}

		void	initialize(std::pair<T*, bool>& pair)
		{
			pair.second = true;
			pair.first->initialize();
		}
	protected:
		std::map<U, std::pair<T*, bool> >	_objects;
	public:
		Source() : _initialize(true) {}

		virtual ~Source()
		{
			typename std::map<U, std::pair<T*, bool> >::iterator it = this->_objects.begin();

			for (; it != this->_objects.end(); ++it)
				delete it->second.first;
		}

		void	add(U const& key, T* object)
		{
			if (this->_objects.find(key) == this->_objects.end())
			{
				this->_initialize = false;
				this->_objects.insert(std::pair<U, std::pair<T*, bool> >(key, std::pair<T*, bool>(object, false)));
			}
		}

		void	del(U const& key)
		{
			typename std::map<U, std::pair<T*, bool> >::iterator it = this->_objects.find(key);

			if (it != this->_objects.end())
			{
				if (!this->_initialize && !it->second.second)
					this->check();
				delete it->second.first;
				this->_objects.erase(it);
			}
		}

		T*		get(U const& key)
		{
			typename std::map<U, std::pair<T*, bool> >::iterator it = this->_objects.find(key);

			if (it != this->_objects.end())
			{
				if (!it->second.second)
					this->initialize(it->second);
				return (it->second.first);
			}
			return (0);
		}

		bool	isInitialize()
		{
			return (this->_initialize);
		}

		void	randomInitialize()
		{
			this->check();
			if (this->_initialize)
			{
				typename std::map<U, std::pair<T*, bool> >::iterator it = this->_objects.begin();
				for (; it != this->_objects.end(); ++it)
					if (!it->second.second)
					{
						this->initialize(it->second);
						break;
					}
			}
		}
	};
}

#endif
