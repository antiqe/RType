#include "SFMLAnimation.hpp"
#include "Core.hpp"
#ifdef _WIN32
#include "WTimer.hpp"
#else
#include "LTimer.hpp"
#endif

std::string const	SFMLAnimation::EXPLOSION1 = "explosion1";
std::string const	SFMLAnimation::EXPLOSION2 = "explosion2";
std::string const	SFMLAnimation::EXPLOSION3 = "explosion3";
std::string const	SFMLAnimation::EXPLOSION4 = "explosion4";
std::string const	SFMLAnimation::ASTEROID1 = "asteroid1";
std::string const	SFMLAnimation::ASTEROID2 = "asteroid2";
std::string const	SFMLAnimation::LOADING = "loading";

SFMLAnimation::Context::Context()
	: frame(0), timer(0)
{
#ifdef _WIN32
	this->timer = new Ultra::WTimer();
#else
	this->timer = new Ultra::LTimer();
#endif
}

SFMLAnimation::Context::~Context()
{
	delete this->timer;
}

SFMLAnimation::SFMLAnimation(std::string const& filename, size_t width, size_t height, float delay, bool repeat)
	: SFMLImage(filename), _delay(delay), _repeat(repeat)
{
	this->_sizeRect = Ultra::Vector2D<size_t>(width, height);
	this->_current = this->_context.end();
}

SFMLAnimation::~SFMLAnimation()
{

}

void	SFMLAnimation::initialize()
{
	if (!this->_filename.empty())
	{
		SFMLImage::initialize();
		size_t	x;
		for (size_t y = 0; y < (size_t)this->_scale.getY(); y += this->_sizeRect.getY())
			for (x = 0; x < (size_t)this->_scale.getX(); x += this->_sizeRect.getX())
				this->_imgs.push_back(new SFMLImage(this->_filename, x, y, this->_sizeRect.getX(), this->_sizeRect.getY()));
		for (x = 0; x < this->_imgs.size(); ++x)
			this->_imgs[x]->initialize();
		if (this->_context.empty())
			this->_context.push_front(new SFMLAnimation::Context());
		this->_current = this->_context.begin();
		this->reset();
	}
}

void	SFMLAnimation::update()
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

void	SFMLAnimation::unload()
{
	while (!this->_context.empty())
	{
		delete this->_context.front();
		this->_context.pop_front();
	}
	while (!this->_imgs.empty())
	{
		delete this->_imgs.back();
		this->_imgs.pop_back();
	}
}

void	SFMLAnimation::draw(Engine::IRender* render)
{
	this->_imgs[(*this->_current)->frame]->setPosition(this->_position);
	this->_imgs[(*this->_current)->frame]->setColor(this->_color);
	this->_imgs[(*this->_current)->frame]->setSize(this->_size);
	this->_imgs[(*this->_current)->frame]->draw(render);
}

void	SFMLAnimation::reset()
{
	for (ContextIterator it = this->_context.begin(); it != this->_context.end(); ++it)
	{
		(*it)->frame = 0;
		(*it)->timer->restart();
	}
}

void	SFMLAnimation::reset(ContextIterator const& context)
{
	(*context)->frame = 0;
	(*context)->timer->restart();
}

bool	SFMLAnimation::isRepeat() const
{
	return (this->_repeat);
}

bool	SFMLAnimation::isStopped() const
{
	for (ContextConstIterator it = this->_context.cbegin(); it != this->_context.cend(); ++it)
		if ((*it)->timer->isRunning())
			return (false);
	return (true);
}

bool	 SFMLAnimation::isStopped(ContextIterator const& context) const
{
	return (!(*context)->timer->isRunning());
}

SFMLAnimation::ContextIterator const&	SFMLAnimation::addContext()
{
	this->_context.push_back(new SFMLAnimation::Context());
	this->_context.front()->timer->start();
	this->_tmp = this->_context.begin();
	return (this->_tmp);
}

void	SFMLAnimation::delContext(ContextIterator const& context)
{
	this->_context.erase(context);
}

void	SFMLAnimation::changeContext(ContextIterator const& context)
{
	this->_current = context;
}