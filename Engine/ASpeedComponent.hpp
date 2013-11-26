#ifndef _ASPEEDCOMPONENT_H_
# define _ASPEEDCOMPONENT_H_

#include "AComponent.hpp"

namespace Engine
{
	class ASpeedComponent : public AComponent
	{
	protected:
		float	_speed;
	public:
		ASpeedComponent(float speed);
		ASpeedComponent(ASpeedComponent const& cpy);
		virtual ~ASpeedComponent();

		std::string const	getFamilyID() const;

		float	getSpeed() const;
		void	setSpeed(float speed);
	};
}

#endif
