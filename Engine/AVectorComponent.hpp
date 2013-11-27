#ifndef _AVECTORCOMPONENT_H_
# define _AVECTORCOMPONENT_H_

#include <cmath>

#include "AComponent.hpp"
#include "Vector.hpp"
#include "Coordinate.hpp"

namespace Engine
{
	template <typename T, int D = Ultra::COORDINATE3DSIZE>
	class AVectorComponent : public AComponent
	{
	protected:
		Ultra::Vector<T, D>	_vector;

		void	normalize()
		{
			float	length = 0.0f;
			int		i;

			for (i = 0; i < D; ++i)
				length += pow(this->_vector.getCoordinate(i), 2.0f);
			if (length)
			{
				length = sqrt(length);
				for (i = 0; i < D; ++i)
					this->_vector.setCoordinate(this->_vector.getCoordinate(i) / length, i);
			}
		}
	public:
		AVectorComponent() : AComponent() {}
		AVectorComponent(AVectorComponent const& cpy) : AComponent(cpy) {}
		virtual ~AVectorComponent() {}

		std::string const	getFamilyID() const
		{
			return (AComponent::VECTOR);
		}

		Ultra::Vector<T, D>	getVector() const
		{
			return (this->_vector);
		}

		void	setVector(Ultra::Vector<T, D> const& vector)
		{
			this->_vector = vector;
			this->normalize();
		}
	};
}

#endif
