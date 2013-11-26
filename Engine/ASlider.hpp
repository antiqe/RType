#ifndef _A_SLIDER_H_
# define _A_SLIDER_H_

#include <string>

#include "Widget.hpp"
#include "IImage.hpp"
#include "Vector2D.hpp"
#include "IRender.hpp"
#include "AStateModule.hpp"
#include "SliderCursor.hpp"
#include "ASourceModule.hpp"

namespace Engine
{
	class ASlider : public Engine::Widget
	{
	protected:
		int						_value;
		int						_max;
		int						_min;
		ASourceModule*			_sourceModule;
		IImage*					_img;
		std::string				_file;
		SliderCursor*			_cursor;

	public:
		ASlider(std::string const &name, std::string const &normalFile, std::string const &normalCursorFile, 
			std::string const &clickedCursorFile, std::string const &hoverCursorFile, 
			Engine::Callback::EventFunction moveCursorCallback,	int min = 0, int max = 100, int defaultValue = 0);
		virtual ~ASlider();

		virtual	void	initialize();
		virtual void	update();
		virtual void	unload();
		virtual void	draw(Engine::IRender* render);

		virtual void	moveCursor(int pos) = 0;
		void			scroll(int delta);

		virtual void	setValue(int value) = 0;
		int				getValue() const;
		int				getMax() const;
		void			setMax(int max);
		int				getMin() const;
		void			setMin(int min);
		unsigned int	getCursorWidth() const;
		unsigned int	getCursorHeight() const;
		void			setCursorSize(unsigned int x, unsigned int y);
		int				getCursorX() const;
		int				getCursorY() const;
		void			setCursorPosition(int x, int y);

		void	hide();
		void	show();
	};
}

#endif