#ifndef _AINVINCIBILITYCOMPONENT_H_
# define _AINVINCIBILITYCOMPONENT_H_

#include <string>

#include "AComponent.hpp"

namespace Engine
{
	class AInvincibilityComponent : public Engine::AComponent
	{
	protected:
		bool	_active;
	public:
		AInvincibilityComponent();
		AInvincibilityComponent(AInvincibilityComponent const& cpy);
		virtual ~AInvincibilityComponent();

		std::string const		getFamilyID() const;

		bool	active() const;
	};
}

#endif