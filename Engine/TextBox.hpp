#ifndef _TEXTBOX_H_
# define _TEXTBOX_H_

#include <string>

#include "Widget.hpp"
#include "IImage.hpp"
#include "IRender.hpp"
#include "IText.hpp"
#include "ITimer.hpp"
#include "ASourceModule.hpp"
#include "IInput.hpp"

namespace Engine
{
	class TextBox : public Engine::Widget
	{
	public:
		enum Status
		{
			SELECTED = 0,
			NORMAL,
			HOVER,
			STATUSSIZE
		};
	private:
		size_t					_limit;
		char					_hide;
		Engine::Keyboard::Key	_lastKey;
		TextBox::Status			_status;
		Ultra::ITimer*			_cursorTimer;
		Ultra::ITimer*			_keyTimer;
		bool					_cursorStatus;
		std::string				_defaultText;
		std::string				_currentText;
		Ultra::Vector2D<int>	_positionText;
		std::string				_fontText;
		Ultra::Color			_colorText;
		size_t					_sizeText;
		unsigned long			_styleText;
		IText*					_text;
		ASourceModule*			_sourceModule;
		bool					_isLocked;
		IImage*					_img[TextBox::STATUSSIZE];
		std::string				_file[TextBox::STATUSSIZE];

		static std::map<int, char> const		_keyMap;
		static std::map<int, char> const		buildKeyMap();
	public:
		TextBox(std::string const& name, std::string const& normal, std::string const &selected, std::string const& hover,
			std::string const& font, size_t limit, std::string const &defaultText = "", char hide = '\0');
		virtual ~TextBox();

		virtual	void	initialize();
		virtual void	update();
		virtual void	unload();
		virtual void	draw(Engine::IRender* render);

		void	lock();
		void	unlock();
		bool	isLocked();

		void	setStatus(TextBox::Status type);
		void	setDefaultText(std::string const& text);
		void	setTextFont(std::string const& fontname);
		void	setTextColor(Ultra::Color const& color);
		void	setTextSize(size_t size);
		void	setTextPosition(int x, int y);
		void	setTextStyle(unsigned long style);
		void	setText(std::string const &text);

		TextBox::Status			getStatus() const;
		std::string const&		getDefaultText() const;
		std::string const&		getTextFont() const;
		size_t					getTextSize() const;
		unsigned long			getTextStyle() const;
		Ultra::Vector2D<int>	getTextPosition() const;
		std::string const&		getText() const;

		void	addCharacter(Engine::Keyboard::Key c);
		void	delCharacter();

		void	setKeyPressed(Engine::Keyboard::Key c);
		void	setKeyReleased(Engine::Keyboard::Key c);

		void	setHeight(size_t height);
	};
}

#endif