#ifndef _CHRONO_H_
# define _CHRONO_H_

# include "IPrototype.hpp"

namespace Ultra
{
	class IChrono : public IPrototype<IChrono>
	{
	public:
		IChrono() {}
		virtual ~IChrono() {}

		virtual void	launch(float) {}
		virtual bool	isFinish() const { return (false); }
		virtual void	stop() {}
		virtual bool	isLaunched() const { return (false); }

		virtual IChrono*	clone() const { return (new IChrono); }
	};
}

#endif