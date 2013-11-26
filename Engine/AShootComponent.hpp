#ifndef _ASHOOTCOMPONENT_H_
# define _ASHOOTCOMPONENT_H_

#include <string>

#include "AComponent.hpp"

namespace Engine
{
	class AShootComponent : public Engine::AComponent
	{
	protected:
		float		_current;
		float const	_max;
	public:
		AShootComponent(float max);
		AShootComponent(AShootComponent const& cpy);
		virtual ~AShootComponent();

		std::string const		getFamilyID() const;

		float	getPower() const;

		virtual void	active() = 0;
		virtual void	shoot() = 0;
	};
}

#endif