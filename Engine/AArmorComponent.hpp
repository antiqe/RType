#ifndef _AARMORCOMPONENT_H_
# define _AARMORCOMPONENT_H_

#include <string>

#include "AComponent.hpp"

namespace Engine
{
	class AArmorComponent : public Engine::AComponent
	{
	protected:
		short		_armor;
		short const	_min;
		short const	_max;
	public:
		AArmorComponent(short armor, short min = -100, short max = 100);
		AArmorComponent(AArmorComponent const& cpy);
		virtual ~AArmorComponent();

		std::string const		getFamilyID() const;

		short	getArmor() const;
		void	setArmor(short armor);
	};
}

#endif