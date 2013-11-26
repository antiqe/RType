#ifndef _ITEXT_H_
# define _ITEXT_H_

#include <string>

#include "IVisualObject.hpp"
#include "Color.hpp"
#include "Vector2D.hpp"

namespace Engine
{
	class IText : public IVisualObject
	{
	public:
		virtual ~IText() {}

		virtual void	setString(std::string const& string) = 0;
		virtual void	setFont(std::string const& fontname) = 0;
		virtual void	setSize(size_t size) = 0;
		virtual void	setPosition(Ultra::Vector2D<int> const &position) = 0;
		virtual void	setColor(Ultra::Color const& color) = 0;
		virtual void	setStyle(unsigned long style) = 0;

		virtual std::string const&			getString() const = 0;
		virtual std::string const&			getFont() const = 0;
		virtual size_t						getSize() const = 0;
		virtual Ultra::Vector2D<int>		getPosition() const = 0;
		virtual Ultra::Color				getColor() const = 0;
		virtual unsigned long				getStyle() const = 0;
	};
}

#endif