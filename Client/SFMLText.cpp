#include "SFMLText.hpp"

std::string const	SFMLText::TEXTBOX = "textbox";

SFMLText::SFMLText(std::string const& string, std::string const& fontname)
	: _fontname(fontname),
	_string(string),
	_text(0),
	_font(0),
	_size(0),
	_style(0),
	  _position(Ultra::Vector2D<int>(0, 0)),
	_color(Ultra::Color(0, 0))
{

}

SFMLText::~SFMLText()
{
	// Probleme WTF lorsqu'on ose delete les deux objets
	/*
	delete this->_font;
	delete this->_text;
	*/
}

void	SFMLText::setString(std::string const& string)
{
	this->_string = string;
	if (this->_text)
		this->_text->setString(this->_string);
}

void	SFMLText::setFont(std::string const& fontname)
{
	this->_fontname = fontname;
	if (this->_font && this->_text && this->_font->loadFromFile(this->_fontname))
		this->_text->setFont(*this->_font);
}

void	SFMLText::setSize(size_t size)
{
	if (this->_text)
		this->_text->setCharacterSize(size);
}

void	SFMLText::setPosition(Ultra::Vector2D<int> const &position)
{
	this->_position = position;
	if (this->_text)
		this->_text->setPosition((float)this->_position.getX(), (float)this->_position.getY());
}

void	SFMLText::setColor(Ultra::Color const& color)
{
	this->_color = color;
	if (this->_text)
		this->_text->setColor(sf::Color(color.getComposante(Ultra::Color::RED),
		color.getComposante(Ultra::Color::GREEN),
		color.getComposante(Ultra::Color::BLUE),
		color.getComposante(Ultra::Color::ALPHA)));
}

void	SFMLText::setStyle(unsigned long style)
{
	this->_style = style;
	if (this->_text)
		this->_text->setStyle(style);
}

std::string const&		SFMLText::getString() const
{
	return (this->_string);
}

std::string const&		SFMLText::getFont() const
{
	return (this->_fontname);
}

size_t					SFMLText::getSize() const
{
	return (this->_size);
}

Ultra::Vector2D<int>	SFMLText::getPosition() const
{
	return (this->_position);
}

Ultra::Color	SFMLText::getColor() const
{
	return (this->_color);
}

unsigned long	SFMLText::getStyle() const
{
	return (this->_style);
}

void	SFMLText::initialize()
{
	this->_text = new sf::Text();
	this->_font = new sf::Font();
	this->_text->setString(this->_string);
	if (this->_font->loadFromFile(this->_fontname))
		this->_text->setFont(*this->_font);
	this->_text->setCharacterSize(this->_size);
	this->_text->setColor(sf::Color(this->_color.getComposante(Ultra::Color::RED),
		this->_color.getComposante(Ultra::Color::GREEN),
		this->_color.getComposante(Ultra::Color::BLUE),
		this->_color.getComposante(Ultra::Color::ALPHA)));
	this->_text->setPosition((float)this->_position.getX(), (float)this->_position.getY());
	this->_text->setStyle(this->_style);
}

void	SFMLText::update()
{

}

void	SFMLText::unload()
{

}

void	SFMLText::draw(Engine::IRender* render)
{
	render->draw(this->_text);
}
