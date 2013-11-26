#ifndef _ATIMER_H_
# define _ATIMER_H_

#include "ITimer.hpp"
#include "Time.hpp"

namespace Ultra
{
	template <int P>
	class ATimer : public ITimer
	{
	private:
		Time<P>		_begin;
		Time<P>		_end;
		bool		_run;
		bool		_stop;
	public:
		ATimer() : _begin(Time<P>()), _end(Time<P>()), _run(false), _stop(false) {}
		~ATimer() {}

		void	start()
		{
			if (!this->isRunning())
			{
				if (this->isStopped())
				{
					this->_begin = this->clock() - (this->_end - this->_begin);
					this->_stop = false;
				}
				else
					this->_begin = this->clock();
				this->_run = true;
			}
		}

		void	stop()
		{
			if (this->isRunning())
			{
				this->_stop = true;
				this->_run = false;
				this->_end = this->clock();
			}
		}

		void	reset()
		{
			this->_begin = Time<P>(0, 0);
			this->_end = Time<P>(0, 0);
			this->_run = false;
			this->_stop = false;
		}

		void	restart()
		{
			this->reset();
			this->start();
		}

		bool	isRunning() const
		{
			return (this->_run);
		}

		bool	isStopped() const
		{
			return (this->_stop);
		}

		bool		isTimeOut(double seconds) const
		{
			Time<P>	time;
			int const	sec = static_cast<int>(seconds);
			int const	usec = static_cast<int>((seconds - static_cast<double>(sec)) * P);

			time = this->isRunning() ? (this->clock() - this->_begin) : (this->_end - this->_begin);
			return (time.sec > sec ? true : (time.sec == sec && time.usec > usec ? true : false));
		}

		double	getTime() const
		{
			Time<P>	time = this->clock() - this->_begin;

			return (static_cast<double>(time.sec) + (static_cast<double>(time.usec) / P));
		}

		virtual Time<P>	clock() const = 0;
	};
}

#endif
