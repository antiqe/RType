#ifndef _AMOVECOMPONENT_H_
# define _AMOVECOMPONENT_H_

#include "AComponent.hpp"

namespace Engine
{
	class AMoveComponent : public AComponent
	{
	public:
		AMoveComponent();
		AMoveComponent(AMoveComponent const& cpy);
		virtual ~AMoveComponent();

		std::string const	getFamilyID() const;
	};
}

#endif
