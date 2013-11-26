#ifndef _ARENDERMODULE_H_
# define _ARENDERMODULE_H_

# include <string>

# include "AModule.hpp"
# include "IRender.hpp"

namespace Engine
{
	class ARenderModule : public AModule
	{
	protected:
		IRender*	_render;
	public:
		ARenderModule(IRender* render);
		virtual ~ARenderModule();

		std::string const&	getID() const;
		IRender*			getRender() const;

		virtual void	draw() = 0;
	};
};

#endif