#ifndef _ASIZECOMPONENT_H_
# define _ASIZECOMPONENT_H_

#include <string>

#include "AComponent.hpp"
#include "Vector.hpp"
#include "Coordinate.hpp"

namespace Engine
{
	template <int D = Ultra::COORDINATE3DSIZE>
	class ASizeComponent : public Engine::AComponent
	{
	protected:
		Ultra::Vector<size_t, D>	_size;	
	public:
		ASizeComponent() : AComponent() {}
		ASizeComponent(ASizeComponent const& cpy) : AComponent(), _size(cpy._size) {}
		virtual ~ASizeComponent() {}

		std::string const	getFamilyID() const
		{
			return (AComponent::SIZE);
		}

		int	getDimension() const
		{
			return (D);
		}

		Ultra::Vector<size_t, D> const&	getSize() const
		{
			return (this->_size);
		}

		void	setSize(Ultra::Vector<size_t, D> const& size)
		{
			this->_size = size;
		}
	};
}

#endif