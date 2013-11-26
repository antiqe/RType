#ifndef _ITIMER_H_
# define _ITIMER_H_

namespace Ultra
{
	class ITimer
	{
	public:
		virtual ~ITimer() {}

		virtual void	start() = 0;
		virtual void	stop() = 0;
		virtual void	reset() = 0;
		virtual void	restart() = 0;
		virtual bool	isRunning() const = 0;
		virtual bool	isStopped() const = 0;
		virtual bool	isTimeOut(double seconds) const = 0;
		virtual double	getTime() const = 0;
	};
}

#endif






