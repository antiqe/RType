#ifndef _H_SLIDER_H_
# define _H_SLIDER_H_

#include <string>

#include "ASlider.hpp"

namespace Engine
{
	class HSlider : public ASlider
	{
	public:
		HSlider(std::string const &name, std::string const &normalFile, std::string const &clickedFile, 
			std::string const &hoverFile, std::string const &barFile, int min = 0, int max = 100, int defaultValue = 0);
		virtual ~HSlider();

		void	initialize();
		void	unload();

		void	moveCursor(int pos);

		void	setValue(int value);

		void	setWidth(size_t w);
		void	setHeight(size_t h);
		void	setX(int x);
		void	setY(int y);
		void	setLocalX(int x);
		void	setLocalY(int y);
	};
}

#endif