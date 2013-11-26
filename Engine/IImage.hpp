#ifndef _IIMAGE_H_
# define _IIMAGE_H_

#include <string>

#include "IVisualObject.hpp"
#include "Color.hpp"
#include "Vector2D.hpp"

namespace Engine
{
	class IImage : public IVisualObject
	{
	public:
		virtual ~IImage() {}

		virtual void	setColor(Ultra::Color const& color) = 0;
		virtual void	setSize(Ultra::Vector2D<size_t> const &size) = 0;
		virtual void	setPosition(Ultra::Vector2D<int> const &position) = 0;

		virtual std::string const&				getFile() const = 0;
		virtual Ultra::Color const&				getColor() const = 0;
		virtual Ultra::Vector2D<size_t> const&	getSize() const = 0;
		virtual Ultra::Vector2D<int> const&		getPosition() const = 0;
	};
}

#endif