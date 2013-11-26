#ifndef _SFMLRENDER_H_
# define _SFMLRENDER_H_

#include <string>
#include <sys/types.h>
#include <SFML/Graphics.hpp>

#include "IRender.hpp"
#include "Event.hpp"
#include "SFMLInput.hpp"

class SFMLRender : public Engine::IRender
{
private:
	sf::RenderWindow*	_window;
	std::string			_title;
	unsigned long		_mode;
	SFMLInput			_input;
public:
	SFMLRender();
	~SFMLRender();

	Engine::Event*	pollEvent();
	void			display();
	void			clear();
	bool			isOpen() const;
	void			open(size_t width, size_t height, std::string const& title, unsigned long mode);
	void			close();
	void			draw(void* drawable);

	int								getX() const;
	int								getY() const;
	Ultra::Vector2D<int>			getPosition() const;
	size_t							getWidth() const;
	size_t							getHeight() const;
	Ultra::Vector2D<size_t>			getSize() const;
	std::string	const&				getTitle() const;
	unsigned long					getMode() const;

	void	setX(int x);
	void	setY(int y);
	void	setPosition(Ultra::Vector2D<int> const& position);
	void	setPosition(int x, int y);
	void	setWidth(size_t width);
	void	setHeight(size_t height);
	void	setSize(Ultra::Vector2D<size_t> const& size);
	void	setSize(size_t width, size_t height);
	void	setTitle(std::string const& title);
	void	setMode(unsigned long mode);
};

#endif