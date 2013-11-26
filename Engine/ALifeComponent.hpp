#ifndef _ALIFECOMPONENT_H_
# define _ALIFECOMPONENT_H_

#include <string>

#include "AComponent.hpp"

namespace Engine
{
	class ALifeComponent : public Engine::AComponent
	{
	protected:
		unsigned int		_current;
		unsigned int const	_max;
	public:
		ALifeComponent(unsigned int max);
		ALifeComponent(unsigned int current, unsigned int max);
		ALifeComponent(ALifeComponent const& cpy);
		virtual ~ALifeComponent();

		std::string const		getFamilyID() const;

		unsigned int	getCurrentLife() const;
		unsigned int	getMaxLife() const;

		void	setCurrentLife(unsigned int life);

		virtual void	takeDamage(unsigned int damage) = 0;
		virtual void	heal(unsigned int heal) = 0;
	};
}

#endif