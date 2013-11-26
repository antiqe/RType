#ifndef _LIST_BOX_H_
# define _LIST_BOX_H_

#include <string>

#include "Widget.hpp"
#include "IImage.hpp"
#include "Vector2D.hpp"
#include "IRender.hpp"
#include "AStateModule.hpp"
#include "ASourceModule.hpp"
#include "ASlider.hpp"
#include "IText.hpp"

namespace Engine
{
	class ListBox : public Engine::Widget
	{
		enum Status
		{
			EVEN = 0,
			ODD,
			FOCUS,
			STATUSSIZE
		};

		typedef	std::pair<std::string, Ultra::Value> line;

		ASourceModule*				_sourceModule;
		IImage*						_img[ListBox::STATUSSIZE];
		std::string					_file[ListBox::STATUSSIZE];
		IText*						_drawer;
		ASlider*					_scrollBar;
		std::list<line>				_content;
		std::list<line>::iterator	_start;
		unsigned int				_nbrLine;
		int							_valueSaved;
		unsigned int				_focus;

		unsigned int			_scrollWidth;
		std::string				_textFont;
		unsigned long			_textStyle;
		Ultra::Color			_textColor;
		Ultra::Color			_focusTextColor;

		void	incrStart(int val = 1);
		void	decrStart(int val = 1);
		void	startAtEnd();
	public:
		ListBox(std::string const &name, std::string const &backgroundFileEven, std::string const &backgroundFileOdd,
			std::string const &backgroundFileFocus, std::string const &sliderBackgroundFile,
			std::string const &normalCursorFile, std::string const &clickedCursorFile,
			std::string const &hoverCursorFile, int nbrLine, std::string const &font);
		virtual ~ListBox();

		virtual	void	initialize();
		virtual void	update();
		virtual void	unload();
		virtual void	draw(Engine::IRender* render);

		void	clear();
		void	push(std::string const &text, Ultra::Value const &data, bool doScroll = false);
		void	scroll(int delta);
		void	startAt(int line);
		void	focus(int nbr);
		void	unfocus();

		void	setScrollWidth(unsigned int width);
		void	setTextFont(std::string const& fontname);
		void	setTextStyle(unsigned long style);
		void	setTextColor(Ultra::Color const& color);
		void	setFocusTextColor(Ultra::Color const& color);

		unsigned int			getScrollWidth() const;
		std::string const&		getTextFont() const;
		unsigned long			getTextStyle() const;
		Ultra::Color const&		getTextColor() const;
		Ultra::Color const&		getFocusTextColor() const;

		unsigned int			getNbrLine() const;
		std::string				getFocusValue() const;
		unsigned int			getFocusLine() const;
		Ultra::Value const&		getFocusData() const;
	};
}

#endif
