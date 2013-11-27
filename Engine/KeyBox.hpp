#ifndef _KEY_BOX_H_
# define _KEY_BOX_H_

#include <string>

#include "Widget.hpp"
#include "IImage.hpp"
#include "IRender.hpp"
#include "IText.hpp"
#include "ASourceModule.hpp"
#include "IInput.hpp"

namespace Engine
{
	class KeyBox : public Engine::Widget
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
		Engine::Keyboard::Key	_lastKey;
		KeyBox::Status			_status;
		std::string				_currentText;
		Ultra::Vector2D<int>	_positionText;
		std::string				_fontText;
		Ultra::Color			_colorText;
		size_t					_sizeText;
		unsigned long			_styleText;
		IText*					_text;
		ASourceModule*			_sourceModule;
		bool					_isLocked;
		IImage*					_img[KeyBox::STATUSSIZE];
		std::string				_file[KeyBox::STATUSSIZE];

		static std::map<int, char> const		_keyMap;
		static std::map<int, char> const		buildKeyMap();
	public:
		KeyBox(std::string const& name, std::string const& normal, std::string const &selected, std::string const& hover,
			std::string const& font, size_t limit);
		virtual ~KeyBox();

		virtual	void	initialize();
		virtual void	update();
		virtual void	unload();
		virtual void	draw(Engine::IRender* render);

		void	lock();
		void	unlock();
		bool	isLocked();

		void	setStatus(KeyBox::Status type);
		void	setTextFont(std::string const& fontname);
		void	setTextColor(Ultra::Color const& color);
		void	setTextSize(size_t size);
		void	setTextPosition(int x, int y);
		void	setTextStyle(unsigned long style);
		void	setText(std::string const &text);

		KeyBox::Status			getStatus() const;
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