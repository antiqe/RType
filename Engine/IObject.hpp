#ifndef _IOBJECT_H_
# define _IOBJECT_H_

namespace Engine
{
	class IObject
	{
	public:
		virtual ~IObject() {}

		virtual void	initialize() = 0;
		virtual void	update() = 0;
		virtual void	unload() = 0;
	};
}

#endif
