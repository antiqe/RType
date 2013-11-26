#ifndef _SFMLTEXT_H_
# define _SFMLTEXT_H_

#include <string>
#include <SFML/Graphics.hpp>
#include <map>

#include "Vector2D.hpp"
#include "Color.hpp"
#include "IInput.hpp"
#include "IVisualObject.hpp"
#include "IText.hpp"

class SFMLText : public Engine::IText
{
private:
	std::string				_fontname;
	std::string				_string;
	sf::Text*				_text;
	sf::Font*				_font;
	size_t					_size;
	unsigned int			_style;
	Ultra::Vector2D<int>	_position;
	Ultra::Color			_color;
public:
	SFMLText(std::string const& string, std::string const& fontname = "");
	~SFMLText();

	void	setString(std::string const& string);
	void	setFont(std::string const& fontname);
	void	setSize(size_t size);
	void	setPosition(Ultra::Vector2D<int> const &position);
	void	setColor(Ultra::Color const& color);
	void	setStyle(unsigned long style);

	std::string const&			getString() const;
	std::string const&			getFont() const;
	size_t						getSize() const;
	Ultra::Vector2D<int>		getPosition() const;
	Ultra::Color				getColor() const;
	unsigned long				getStyle() const;

	void	initialize();
	void	update();
	void	unload();
	void	draw(Engine::IRender* render);

	static std::string const	TEXTBOX;
};

#endif