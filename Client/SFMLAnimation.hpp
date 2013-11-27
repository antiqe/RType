#ifndef _SFMLANIMATION_H_
# define _SFMLANIMATION_H_

#include <string>
#include <vector>
#include <list>

#include "Vector2D.hpp"
#include "IImage.hpp"
#include "Color.hpp"
#include "SFMLImage.hpp"
#include "ITimer.hpp"

class SFMLAnimation : public SFMLImage
{
private:
	struct Context
	{
		Context();
		~Context();
		size_t			frame;
		Ultra::ITimer*	timer;
	};
public:
	typedef std::list<Context*>::iterator		ContextIterator;
	typedef std::list<Context*>::const_iterator	ContextConstIterator;
private:
	float							_delay;
	bool							_repeat;
	ContextIterator					_current;
	ContextIterator					_tmp;
	std::list<Context*>				_context;		
	std::vector<Engine::IImage*>	_imgs;
public:
	SFMLAnimation(std::string const& filename, size_t width, size_t height, float delay = 1.0f, bool repeat = true);
	~SFMLAnimation();

	void	initialize();
	void	update();
	void	unload();
	void	draw(Engine::IRender* render);
	void	reset();
	void	reset(ContextIterator const& context);

	bool	isRepeat() const;
	bool	isStopped() const;
	bool	isStopped(ContextIterator const& context) const;

	ContextIterator const&	addContext();
	void					delContext(ContextIterator const& context);
	void					changeContext(ContextIterator const& context);

	static std::string const	EXPLOSION1;
	static std::string const	EXPLOSION2;
	static std::string const	EXPLOSION3;
	static std::string const	EXPLOSION4;
	static std::string const	ASTEROID1;
	static std::string const	ASTEROID2;
	static std::string const	LOADING;

	static std::string const	STARSHIP2;
	static std::string const	STARSHIP3;
	static std::string const	STARSHIP4;
};

#endif
