#ifndef _ACHRONO_H_
# define _ACHRONO_H_

#include "IChrono.hpp"
#include "Time.hpp"

namespace Ultra
{
	template <int P>
	class AChrono : public IChrono
	{
	protected:
		bool	_launch;
		float	_delay;
		Time<P>	_time;
	public:
		AChrono()
			: _launch(false), _delay(0.0f)
		{

		}

		virtual ~AChrono()
		{

		}

		void	launch(float delay)
		{
			this->_launch = true;
			this->_delay = delay;
			this->_time = this->clock();
		}

		void	stop()
		{
			this->_launch = false;
		}

		bool	isLaunched() const
		{
			return (this->_launch);
		}

		bool	isFinish() const
		{
			if (this->_launch)
			{
				Time<P>		time = this->clock() - this->_time;
				int const	sec = static_cast<int>(this->_delay);
				int const	usec = static_cast<int>((this->_delay - static_cast<double>(sec)) * P);
				return (time.sec > sec ? true : (time.sec == sec && time.usec > usec ? true : false));
			}
			return (false);
		}

		virtual Time<P>	clock() const = 0;
	};
}

#endif