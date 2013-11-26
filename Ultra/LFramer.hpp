#ifndef _LFRAMER_H_
# define _LFRAMER_H_

#include <sys/types.h>

#include "AFramer.hpp"

namespace Ultra
{
	class LFramer : public AFramer
	{
	public:
		LFramer(size_t frame);
		virtual ~LFramer();

		virtual bool		wait() const;
		virtual double	time() const;
	};
}

#endif /* _LFRAMER_H_ */
