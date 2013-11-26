#ifndef _ASHIELDCOMPONENT_H_
# define _ASHIELDCOMPONENT_H_

#include <string>

#include "AComponent.hpp"

namespace Engine
{
	class AShieldComponent : public Engine::AComponent
	{
	protected:
		unsigned int	_shield;
	public:
		AShieldComponent(unsigned int shield = 0);
		AShieldComponent(AShieldComponent const& cpy);
		virtual ~AShieldComponent();

		std::string const		getFamilyID() const;

		unsigned int	getShield() const;
		void			setShield(unsigned int shield);

		bool			isActive() const;
		
		virtual unsigned int	takeDamage(unsigned int damage) = 0;
	};
}

#endif