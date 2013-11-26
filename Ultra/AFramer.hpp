#ifndef _AFRAMER_H_
# define _AFRAMER_H_

#include <sys/types.h>

namespace Ultra
{
	class AFramer
	{
	protected:
		size_t	_frame;
		double	_fps;
		double	_start;
		double	_end;

		inline void	calcFPS();
		double		latence() const;
	public:
		AFramer(size_t frame);
		virtual ~AFramer();

		void	start();
		void	end();
		void	reset();

		size_t		getFrame() const;
		void		setFrame(size_t frame);

		virtual bool	wait() const = 0;
		virtual double	time() const = 0;
	};
}

#endif /* _AFRAMER_H_ */
