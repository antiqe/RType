#ifndef __ASTATE_H__
# define __ASTATE_H__

# include <string>

# include "Widget.hpp"

namespace Engine
{
	class AState : public Widget
	{
	public:
		AState(std::string const& name);
		virtual ~AState() {}

		virtual void	reset() = 0;
		virtual void	reload() = 0;
		virtual void	resize(size_t width, size_t height) = 0;
	};
}

#endif