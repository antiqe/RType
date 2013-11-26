#ifndef _APARALLAX_H_
# define _APARALLAX_H_

#include <string>

#include "Widget.hpp"
#include "Background.hpp"

namespace Engine
{
	class AParallax : public Engine::Widget
	{
	public:
		enum Type
		{
			BEGIN,
			END,
			TYPESIZE
		};
	protected:
		float		_z;
		Background	_img;
		float		_x[AParallax::TYPESIZE];
		float		_y[AParallax::TYPESIZE];
	public:
		AParallax(std::string const& name, std::string const& file, float z = 1.0f, Ultra::Color const& color = Ultra::Color(255));
		~AParallax();

		void	setWidth(size_t w);
		void	setHeight(size_t h);
		void	setX(int x);
		void	setY(int y);
		void	setLocalX(int x);
		void	setLocalY(int y);

		virtual void	scroll() = 0;
	};
}

#endif