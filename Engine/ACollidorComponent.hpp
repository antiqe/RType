#ifndef _ACOLLIDORCOMPONENT_H_
# define _ACOLLIDORCOMPONENT_H_

#include <string>

#include "AComponent.hpp"

namespace Engine
{
	class ACollidorComponent : public Engine::AComponent
	{
	public:
		ACollidorComponent();
		ACollidorComponent(ACollidorComponent const& cpy);
		virtual ~ACollidorComponent();

		std::string const		getFamilyID() const;

		virtual bool	hit(ACollidorComponent* collidor) = 0;
	};
}

#endif