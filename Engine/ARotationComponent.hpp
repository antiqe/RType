#ifndef _AROTATIONCOMPONENT_H_
# define _AROTATIONCOMPONENT_H_

#include <string>

#include "AComponent.hpp"
#include "Vector.hpp"

namespace Engine
{
	template <int D = 3>
	class ARotationComponent : public Engine::AComponent
	{
	protected:
		static float			_PI = 3.14159;
		Ultra::Vector<short, D>	_degree;
		Ultra::Vector<float, D>	_radian;
	public:
		ARotationComponent() : AComponent() {}
		ARotationComponent(ARotationComponent const& cpy) : AComponent(), _degree(cpy._degree), _radian(cpy._radian)
		virtual ~ARotationComponent() {}

		std::string const		getFamilyID() const
		{
			return (AComponent::ROTATION);
		}

		void	setDegree(int degree, Ultra::Coordinate coordinate)
		{
			this->_degree.setCoordinate(degree, coordinate);
			this->_radian.setCoordinate((float)degree / 180.0f * ARotationComponent::_PI);
		}
		void	setRadian(float radian, Ultra::Coordinate coordinate)
		{
			this->_radian.setCoordinate(radian, coordinate);
			this->_degree.setCoordinate((int)(radian / ARotationComponent::_PI * 180.0f)
		}

		int	getDimension() const
		{
			return (D);
		}

		int	getDegree(Ultra::Coordinate coordinate) const
		{
			return (this->_degree.getCoordinate(coordinate));
		}

		int	getRadian(Ultra::Coordinate coordinate) const
		{
			return (this->_radian.getCoordinate(coordinate));
		}
	};
}

#endif