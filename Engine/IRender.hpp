#ifndef _IRENDER_H_
# define _IRENDER_H_

#include <sys/types.h>
#include <string>

#include "Vector2D.hpp"
#include "Event.hpp"

namespace Engine
{
	class IRender
	{
	public:
		virtual ~IRender() {}

		virtual Event*	pollEvent() = 0;
		virtual void	display() = 0;
		virtual void	clear() = 0;
		virtual bool	isOpen() const = 0;
		virtual void	open(size_t width, size_t height, std::string const& title, unsigned long mode = 0) = 0;
		virtual void	close() = 0;
		virtual void	draw(void* drawable) = 0;

		virtual int								getX() const = 0;
		virtual int								getY() const = 0;
		virtual Ultra::Vector2D<int>			getPosition() const = 0;
		virtual size_t							getWidth() const = 0;
		virtual size_t							getHeight() const = 0;
		virtual Ultra::Vector2D<size_t>			getSize() const = 0;
		virtual std::string	const&				getTitle() const = 0;
		virtual unsigned long					getMode() const = 0;

		virtual void	setX(int x) = 0;
		virtual void	setY(int y) = 0;
		virtual void	setPosition(Ultra::Vector2D<int> const& position) = 0;
		virtual void	setPosition(int x, int y) = 0;
		virtual void	setWidth(size_t width) = 0;
		virtual void	setHeight(size_t height) = 0;
		virtual void	setSize(Ultra::Vector2D<size_t> const& size) = 0;
		virtual void	setSize(size_t width, size_t height) = 0;
		virtual void	setTitle(std::string const& title) = 0;
		virtual void	setMode(unsigned long mode) = 0;
	};	
}

#endif