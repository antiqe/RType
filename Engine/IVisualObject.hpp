#ifndef _IVISUALOBJECT_H_
# define _IVISUALOBJECT_H_

#include "IObject.hpp"
#include "IRender.hpp"

namespace Engine
{
	class IVisualObject : public IObject
	{
	public:
		virtual ~IVisualObject() {}

		virtual void	draw(IRender*) = 0;
	};
}

#endif