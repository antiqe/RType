#ifndef _VECTOR_H_
# define _VECTOR_H_

#include <string>

#include "Exception.hpp"
#include "Coordinate.hpp"

namespace Ultra
{
	template <typename T = int, int D = COORDINATE3DSIZE>
	class Vector
	{
	protected:
		T	_table[D];
	public:
		Vector() 
		{ 
			for (int i = 0; i < D; ++i)
				this->_table[i] = static_cast<T>(0); 
		}

		Vector(Vector<T, D> const& cpy)
		{
			for (int i = 0; i < D; ++i)
				this->_table[i] = cpy._table[i];
		}

		Vector<T, D>&	operator=(Vector<T, D> const& cpy)
		{
			if (this != &cpy)
				for (int i = 0; i < D; ++i)
					this->_table[i] = cpy._table[i];
			return (*this);
		}

		virtual ~Vector() {}

		T		getCoordinate(int i) const 
		{ 
			return (this->_table[i]); 
		}

		int		getDimension() const 
		{ 
			return (D);
		}

		void	setCoordinate(T const& coordinate, int i)
		{ 
			this->_table[i] = coordinate; 
		}

		Vector<T, D>	operator+(Vector<T, D> const& cpy)
		{
			Vector<T, D>	v;

			for (int i = 0; i < D; ++i)
				v._table[i] = this->_table[i] + cpy._table[i];
			return (v);
		}
	};
}

#endif /* _VECTOR_H_ */
