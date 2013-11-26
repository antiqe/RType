#include "AFramer.hpp"

namespace Ultra
{
	AFramer::AFramer(size_t frame)
		: _frame(frame), _fps(0.0f), _start(-1.0f), _end(-1.0f)
	{
		this->calcFPS();
	}

	AFramer::~AFramer()
	{

	}

	void	AFramer::calcFPS()
	{ 
		this->_fps = this->_frame ? 1.0f / (double)(this->_frame) : 0.0f; 
	}

	double	AFramer::latence() const
	{
		double	exectime = this->_end - this->_start;

		if (this->_end == -1.0f || this->_start == -1.0f)
			return (0.0f);
		return (exectime > this->_fps ? 0.0f : this->_fps - exectime);
	}

	void	AFramer::start()
	{
		this->_start = this->time();
		this->_end = -1.0f;
	}

	void	AFramer::end()
	{
		this->_end = this->time();
	}

	void	AFramer::reset()
	{
		this->_start = -1.0f;
		this->_end = -1.0f;
	}

	size_t	AFramer::getFrame() const
	{
		return (this->_frame);
	}

	void	AFramer::setFrame(size_t frame)
	{
		this->_frame = frame;
		this->calcFPS();
	}
}