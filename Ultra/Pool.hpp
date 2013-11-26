#ifndef _POOL_H_
# define _POOL_H_

#include <sys/types.h>
#include <stack>

namespace Ultra
{
	template <typename T>
	class Pool
	{
	private:
		T const			_object;
		size_t			_max;
		size_t			_cur;
		size_t			_limit;
		size_t			_idx;
		std::stack<T*>	_objects;
	public:
		Pool(T const& object, size_t limit, size_t base = -1)
			: _object(object), _limit(limit), _idx(base)
		{
			if ((int)base == -1)
				this->_idx = limit;
			for (size_t i = 0; i < this->_idx; ++i)
				this->_objects.push(object.clone());
		}

		virtual ~Pool()
		{
			while (!this->_objects.empty())
			{
				delete this->_objects.top();
				this->_objects.pop();
			}
		}

		T*		pop()
		{
			if (this->_objects.empty())
				return (this->_object.clone());
			else
			{
				T*	object = this->_objects.top();
				this->_objects.pop();
				--this->_idx;
				return (object);
			}
		}

		void	push(T* object)
		{
			if (this->_idx == this->_limit)
				delete object;
			else
			{
				++this->_idx;
				this->_objects.push(object);
			}
		}

		void	setLimit(size_t limit)
		{
			this->_limit = limit;
			while (this->_idx > this->_limit)
				delete this->pop();
		}

		size_t	getLimit() const
		{
			return (this->_limit);
		}
	};
}

#endif /* _POOL_H_ */
