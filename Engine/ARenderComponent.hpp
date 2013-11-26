#ifndef _ARENDERCOMPONENT_H_
# define _ARENDERCOMPONENT_H_

#include <string>

#include "AComponent.hpp"
#include "IRender.hpp"

namespace Engine
{
	class ARenderComponent : public Engine::AComponent
	{
	public:
		ARenderComponent();
		ARenderComponent(ARenderComponent const& cpy);
		virtual ~ARenderComponent();

		std::string const		getFamilyID() const;

		virtual void	draw(Engine::IRender* render) = 0;
	};
}

#endif