#ifndef _VECTOR2D_H_
# define _VECTOR2D_H_

#include "Vector.hpp"
#include "Coordinate.hpp"

namespace Ultra
{
	template <typename T>
	class Vector2D : protected Vector<T, COORDINATE2DSIZE>
	{
	public:
		Vector2D(T x = static_cast<T>(0), T y = static_cast<T>(0))
		{
			this->_table[0] = x;
			this->_table[1] = y;
		}

	  Vector2D(Vector<T, 2> const& cpy)
		{
			this->_table[0] = cpy._table[0];
			this->_table[1] = cpy._table[1];
		}

		~Vector2D() {}

		Vector2D<T>	operator=(Vector2D<T> const& cpy)
		{
			if (this != &cpy)
			{
				this->_table[0] = cpy._table[0];
				this->_table[1] = cpy._table[1];
			}
			return (*this);
		}

		T	getX() const
		{
			return (this->_table[0]);
		}

		T	getY() const
		{
			return (this->_table[1]);
		}

		void	setX(T x)
		{
			this->_table[0] = x;
		}

		void	setY(T y)
		{
			this->_table[1] = y;
		}

		Vector2D<T>	operator+(Vector2D<T> const& cpy)
		{
			Vector2D<T>	v;

			v.setX(this->_table[0] + cpy._table[0]);
			v.setY(this->_table[1] + cpy._table[1]);
			return (v);
		}
	};
}

#endif /* _VECTOR2D_H_ */
