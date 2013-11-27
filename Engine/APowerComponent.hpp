#ifndef _APOWERCOMPONENT_H_
# define _APOWERCOMPONENT_H_

#include <string>

#include "AComponent.hpp"

namespace Engine
{
	class APowerComponent : public Engine::AComponent
	{
	protected:
		unsigned short		_power;
	public:
		APowerComponent(unsigned short power);
		APowerComponent(APowerComponent const& cpy);
		virtual ~APowerComponent();

		std::string const		getFamilyID() const;

		unsigned short		getPower() const;
		void		setPower(unsigned short power);
	};
}

#endif