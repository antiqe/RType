#ifndef _WFRAMER_H_
# define _WFRAMER_H_

#include <sys/types.h>

#include "AFramer.hpp"

namespace Ultra
{
	class WFramer : public AFramer
	{
	public:
		WFramer(size_t frame);
		virtual ~WFramer();

		virtual bool		wait() const;
		virtual double	time() const;
	};
}

#endif /* _WFRAMER_H_ */
