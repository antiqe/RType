#ifndef _LABEL_H_
# define _LABEL_H_

#include <string>

#include "Widget.hpp"
#include "IRender.hpp"
#include "IText.hpp"
#include "ITimer.hpp"
#include "ASourceModule.hpp"

namespace Engine
{
	class Label : public Engine::Widget
	{
	private:
		std::string				_content;
		std::string				_fontText;
		Ultra::Color			_colorText;
		size_t					_sizeText;
		unsigned long			_styleText;
		Ultra::Vector2D<int>	_positionText;
		ASourceModule*			_sourceModule;
		Engine::IText*			_text;

	public:
		Label(std::string const& name, std::string const& font, std::string const &content = "");
		virtual ~Label();

		virtual	void	initialize();
		virtual void	update();
		virtual void	unload();
		virtual void	draw(Engine::IRender* render);

		void	setContent(std::string const& text);
		void	setTextFont(std::string const& fontname);
		void	setTextColor(Ultra::Color const& color);
		void	setTextSize(size_t size);
		void	setTextPosition(int x, int y);
		void	setTextStyle(unsigned long style);

		std::string const&		getContent() const;
		std::string const&		getTextFont() const;
		size_t					getTextSize() const;
		unsigned long			getTextStyle() const;
		Ultra::Vector2D<int>	getTextPosition() const;
	};
}

#endif