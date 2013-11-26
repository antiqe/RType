#ifndef _IANIMATION_H_
# define _IANIMATION_H_

#include <string>
#include <list>

#include "IVisualObject.hpp"
#include "Color.hpp"
#include "Vector2D.hpp"

namespace Engine
{
	class IAnimation : public IVisualObject
	{
	public:
		typedef std::list<Context*>::iterator		ContextIterator;
		typedef std::list<Context*>::const_iterator	ContextConstIterator;

		virtual ~IAnimation() {}

		void	reset();
		void	reset(ContextIterator const& context);

		bool	isRepeat() const;
		bool	isStopped() const;
		bool	isStopped(ContextIterator const& context) const;

		ContextIterator const&	addContext();
		void					delContext(ContextIterator const& context);
		void					changeContext(ContextIterator const& context);
	};
}

#endif