#ifndef _APOSITIONCOMPONENT_H_
# define _APOSITIONCOMPONENT_H_

#include "AComponent.hpp"
#include "Coordinate.hpp"
#include "Vector.hpp"

namespace Engine
{
	template <typename T, int D = Ultra::COORDINATE3DSIZE>
	class APositionComponent : public AComponent
	{
	protected:
		Ultra::Vector<T, D>	_position;
	public:
		APositionComponent() : AComponent() {}
		APositionComponent(APositionComponent<T, D> const& cpy) : AComponent(cpy), _position(cpy._position) {}
		virtual ~APositionComponent() {}

		std::string const	getFamilyID() const
		{
			return (AComponent::POSITION);
		}

		int	getDimension() const
		{
			return (D);
		}

		Ultra::Vector<T, D> const&	getPosition() const
		{
			return (this->_position);
		}

		void	setPosition(Ultra::Vector<T, D> const& position)
		{
			this->_position = position;
		}
	};
}

#endif