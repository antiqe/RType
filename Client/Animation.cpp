#include "Animation.hpp"
#include "Core.hpp"
#ifdef _WIN32
#include "WTimer.hpp"
#else
#include "LTimer.hpp"
#endif

std::string const	Animation::EXPLOSION1 = "explosion1";
std::string const	Animation::EXPLOSION2 = "explosion2";
std::string const	Animation::EXPLOSION3 = "explosion3";
std::string const	Animation::EXPLOSION4 = "explosion4";
std::string const	Animation::ASTEROID1 = "asteroid1";
std::string const	Animation::ASTEROID2 = "asteroid2";
std::string const	Animation::LOADING = "loading";

Animation::Context::Context()
	: frame(0), timer(0)
{
#ifdef _WIN32
	this->timer = new Ultra::WTimer();
#else
	this->timer = new Ultra::LTimer();
#endif
}

Animation::Context::~Context()
{
	delete this->timer;
}

Animation::Animation(std::string const& filename, size_t width, size_t height, float delay, bool repeat)
	: Image(filename), _delay(delay), _repeat(repeat)
{
	this->_sizeRect = Ultra::Vector2D<size_t>(width, height);
	this->_current = this->_context.end();
}

Animation::~Animation()
{

}

void	Animation::initialize()
{
	if (!this->_filename.empty())
	{
		Image::initialize();
		size_t	x;
		for (size_t y = 0; y < (size_t)this->_scale.getY(); y += this->_sizeRect.getY())
			for (x = 0; x < (size_t)this->_scale.getX(); x += this->_sizeRect.getX())
				this->_imgs.push_back(Image(this->_filename, x, y, this->_sizeRect.getX(), this->_sizeRect.getY()));
		for (x = 0; x < this->_imgs.size(); ++x)
			this->_imgs[x].initialize();
		if (this->_context.empty())
			this->_context.push_front(new Animation::Context());
		this->_current = this->_context.begin();
		this->reset();
	}
}

void	Animation::update()
{
	for (ContextIterator it = this->_context.begin(); it != this->_context.end(); ++it)
	{
		if ((*it)->timer->isTimeOut(this->_delay))
		{
			if ((*it)->frame == (this->_imgs.size() - 1) && !this->_repeat)
				(*it)->timer->reset();
			else
			{
				(*it)->timer->restart();
				(*it)->frame = ((*it)->frame + 1 ) % this->_imgs.size();
			}
		}
	}
}

void	Animation::unload()
{
	while (!this->_context.empty())
	{
		delete this->_context.front();
		this->_context.pop_front();
	}
}

void	Animation::draw(Engine::IRender* render)
{
	this->_imgs[(*this->_current)->frame].setPosition(this->_position);
	this->_imgs[(*this->_current)->frame].setColor(this->_color);
	this->_imgs[(*this->_current)->frame].setSize(this->_size);
	this->_imgs[(*this->_current)->frame].draw(render);
}

void	Animation::reset()
{
	for (ContextIterator it = this->_context.begin(); it != this->_context.end(); ++it)
	{
		(*it)->frame = 0;
		(*it)->timer->restart();
	}
}

void	Animation::reset(ContextIterator const& context)
{
	(*context)->frame = 0;
	(*context)->timer->restart();
}

bool	Animation::isRepeat() const
{
	return (this->_repeat);
}

bool	Animation::isStopped() const
{
	for (ContextConstIterator it = this->_context.begin(); it != this->_context.end(); ++it)
		if ((*it)->timer->isRunning())
			return (false);
	return (true);
}

bool	 Animation::isStopped(ContextIterator const& context) const
{
	return (!(*context)->timer->isRunning());
}

Animation::ContextIterator const&	Animation::addContext()
{
	this->_context.push_back(new Animation::Context());
	this->_context.front()->timer->start();
	this->_tmp = this->_context.begin();
	return (this->_tmp);
}

void	Animation::delContext(ContextIterator const& context)
{
	this->_context.erase(context);
}

void	Animation::changeContext(ContextIterator const& context)
{
	this->_current = context;
}
