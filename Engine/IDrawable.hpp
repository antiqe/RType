#ifndef _IDRAWABLE_H_
# define _IDRAWABLE_H_

#include "IRender.hpp"

namespace Engine
{
	class IDrawable
	{
	public:
		virtual ~IDrawable() {}

		virtual void	draw(IRender* render) = 0;
	};
}

#endif