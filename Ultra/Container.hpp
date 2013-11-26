#ifndef _CONTAINER_H_
# define _CONTAINER_H_

# include <list>
# include <string>
# include <algorithm>

# include "IPrototype.hpp"

namespace Ultra
{
	template <typename T>
	class Container
	{
	protected:
		std::list<T*>	_contents;
	public:
		Container() {}

		Container(Container const& cpy)
		{
			typename std::list<T*>::const_iterator	it;

			for (it = cpy._contents.begin(); it != cpy._contents.end(); ++it)
				this->setContent((*it)->clone());
		}

		virtual ~Container() 
		{
			this->clearContents();
		}

		Container&	operator=(Container const& cpy)
		{
			if (this != &cpy)
			{
				typename std::list<T*>::const_iterator	it;
				this->clearContents();
				for (it = cpy._contents.begin(); it != cpy._contents.end(); ++it)
					this->setContent((*it)->clone());
			}
			return (*this);
		}

		T*	getContent(std::string const& id) const
		{
			typename std::list<T*>::const_iterator it;

			it = std::find_if(this->_contents.begin(), this->_contents.end(), typename T::Compare(id));
			return (it == this->_contents.end() ? (T*)0 : *it);
		}

		T*	setContent(T* content)
		{
			if (!content)
				return (0);
			typename std::list<T*>::iterator it;
			std::string	id = content->getID();
			it = std::find_if(this->_contents.begin(), this->_contents.end(), typename T::Compare(id));
			T*	old = 0;
			if (it != this->_contents.end())
			{
				old = (*it);
				this->_contents.erase(it);
			}
			this->_contents.push_back(content);
			return (old);
		}

		T*	delContent(std::string const& id)
		{
			typename std::list<T*>::iterator	it;

			it = std::find_if(this->_contents.begin(), this->_contents.end(), typename T::Compare(id));
			if (it == this->_contents.end())
				return (0);
			T*	content = *it;
			this->_contents.erase(it);
			return (content);
		}

		void	clearContents()
		{
			while (!this->_contents.empty())
			{
				delete this->_contents.front();
				this->_contents.pop_front();
			}
		}
	};
}

#endif