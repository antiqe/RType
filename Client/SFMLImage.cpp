#include "SFMLImage.hpp"
#include "Core.hpp"

std::string const	SFMLImage::TEXTBOX = "textbox";
std::string const	SFMLImage::TEXTBOX_HOVER = "textbox_hover";
std::string const	SFMLImage::TEXTBOX_SELECTED = "textbox_selected";

std::string const	SFMLImage::BUTTON_BACK = "button_back";
std::string const	SFMLImage::BUTTON_HOVER_BACK = "button_hover_back";
std::string const	SFMLImage::BUTTON_CLICKED_BACK = "button_clicked_back";
std::string const	SFMLImage::BUTTON_QUIT = "button_quit";
std::string const	SFMLImage::BUTTON_HOVER_QUIT = "button_hover_quit";
std::string const	SFMLImage::BUTTON_CLICKED_QUIT = "button_clicked_quit";
std::string const	SFMLImage::BUTTON_LOGIN = "button_login";
std::string const	SFMLImage::BUTTON_HOVER_LOGIN = "button_hover_login";
std::string const	SFMLImage::BUTTON_CLICKED_LOGIN = "button_clicked_login";
std::string const	SFMLImage::BUTTON_SETTINGS = "button_settings";
std::string const	SFMLImage::BUTTON_HOVER_SETTINGS = "button_hover_settings";
std::string const	SFMLImage::BUTTON_CLICKED_SETTINGS = "button_clicked_settings";
std::string const	SFMLImage::BUTTON_CREATE = "button_create";
std::string const	SFMLImage::BUTTON_HOVER_CREATE = "button_hover_create";
std::string const	SFMLImage::BUTTON_CLICKED_CREATE = "button_clicked_create";
std::string const	SFMLImage::BUTTON_JOIN = "button_join";
std::string const	SFMLImage::BUTTON_HOVER_JOIN = "button_hover_join";
std::string const	SFMLImage::BUTTON_CLICKED_JOIN = "button_clicked_join";
std::string const	SFMLImage::BUTTON_OK = "button_ok";
std::string const	SFMLImage::BUTTON_HOVER_OK = "button_hover_ok";
std::string const	SFMLImage::BUTTON_CLICKED_OK = "button_clicked_ok";
std::string const	SFMLImage::BUTTON_SELECT = "button_select";
std::string const	SFMLImage::BUTTON_HOVER_SELECT = "button_hover_select";
std::string const	SFMLImage::BUTTON_CLICKED_SELECT = "button_clicked_select";
std::string const	SFMLImage::BUTTON_REFRESH = "button_refresh";
std::string const	SFMLImage::BUTTON_HOVER_REFRESH = "button_hover_refresh";
std::string const	SFMLImage::BUTTON_CLICKED_REFRESH = "button_clicked_refresh";
std::string const	SFMLImage::BUTTON_GO = "button_go";
std::string const	SFMLImage::BUTTON_HOVER_GO = "button_hover_go";
std::string const	SFMLImage::BUTTON_CLICKED_GO = "button_clicked_go";
std::string const	SFMLImage::BUTTON_NEXT = "button_next";
std::string const	SFMLImage::BUTTON_HOVER_NEXT = "button_hover_next";
std::string const	SFMLImage::BUTTON_CLICKED_NEXT = "button_clicked_next";
std::string const	SFMLImage::BUTTON_PREV = "button_prev";
std::string const	SFMLImage::BUTTON_HOVER_PREV = "button_hover_prev";
std::string const	SFMLImage::BUTTON_CLICKED_PREV = "button_clicked_prev";

std::string const	SFMLImage::CHECKBOX_CHECKED_NORMAL_PRIVATE = "checkbox_checked_normal_private";
std::string const	SFMLImage::CHECKBOX_CHECKED_CLICKED_PRIVATE = "checkbox_checked_clicked_private";
std::string const	SFMLImage::CHECKBOX_CHECKED_HOVER_PRIVATE = "checkbox_checked_hover_private";
std::string const	SFMLImage::CHECKBOX_UNCHECKED_NORMAL_PRIVATE = "checkbox_unchecked_normal_private";
std::string const	SFMLImage::CHECKBOX_UNCHECKED_CLICKED_PRIVATE = "checkbox_unchecked_clicked_private";
std::string const	SFMLImage::CHECKBOX_UNCHECKED_HOVER_PRIVATE = "checkbox_unchecked_hover_private";
std::string const	SFMLImage::CHECKBOX_CHECKED_NORMAL_READY = "checkbox_checked_normal_ready";
std::string const	SFMLImage::CHECKBOX_CHECKED_CLICKED_READY = "checkbox_checked_clicked_ready";
std::string const	SFMLImage::CHECKBOX_CHECKED_HOVER_READY = "checkbox_checked_hover_ready";
std::string const	SFMLImage::CHECKBOX_UNCHECKED_NORMAL_READY = "checkbox_unchecked_normal_ready";
std::string const	SFMLImage::CHECKBOX_UNCHECKED_CLICKED_READY = "checkbox_unchecked_clicked_ready";
std::string const	SFMLImage::CHECKBOX_UNCHECKED_HOVER_READY = "checkbox_unchecked_hover_ready";

std::string const	SFMLImage::SLIDER = "slider";
std::string const	SFMLImage::SLIDER_CURSOR_NORMAL = "slider_cursor_normal";
std::string const	SFMLImage::SLIDER_CURSOR_CLICKED = "slider_cursor_clicked";
std::string const	SFMLImage::SLIDER_CURSOR_HOVER = "slider_cursor_hover";

std::string const	SFMLImage::LISTBOX_EVEN = "list_box_even";
std::string const	SFMLImage::LISTBOX_ODD = "list_box_odd";
std::string const	SFMLImage::LISTBOX_FOCUS = "list_box_focus";

std::string const	SFMLImage::GAUGE_BACKGROUND = "gauge_background";
std::string const	SFMLImage::GAUGE_FILLED = "gauge_filled";

std::string const	SFMLImage::CONNECTION_BACKGROUND = "connection_background";
std::string const	SFMLImage::PLAY_BACKGROUND = "play_background";
std::string const	SFMLImage::JOIN_BACKGROUND = "join_background";
std::string const	SFMLImage::ROOM_BACKGROUND = "room_background";
std::string const	SFMLImage::BACKGROUND = "background";

std::string const	SFMLImage::TERRE = "terre";
std::string const	SFMLImage::POWER = "power";
std::string const	SFMLImage::ARMOR = "armor";
std::string const	SFMLImage::SPEED = "speed";

SFMLImage::SFMLImage(std::string const& filename)
	: _cut(false), _filename(filename)
{

}

SFMLImage::SFMLImage(std::string const& filename, int x, int y, size_t width, size_t height)
	: _cut(true), _filename(filename),  _sizeRect(Ultra::Vector2D<size_t>(width, height)), _positionRect(Ultra::Vector2D<int>(x, y))
{

}

SFMLImage::~SFMLImage()
{

}

void	SFMLImage::setColor(Ultra::Color const& color)
{
	this->_color = color;
	this->_sprite.setColor(sf::Color(this->_color.getComposante(Ultra::Color::RED),
		this->_color.getComposante(Ultra::Color::GREEN),
		this->_color.getComposante(Ultra::Color::BLUE),
		this->_color.getComposante(Ultra::Color::ALPHA)));
}

void	SFMLImage::setPosition(Ultra::Vector2D<int> const &position)
{
	this->_position = position;
	this->_sprite.setPosition((float)this->_position.getX(), (float)this->_position.getY());
}

void	SFMLImage::setSize(Ultra::Vector2D<size_t> const &size)
{
	this->_size = size;
	if (!this->_scale.getX() || !this->_scale.getY())
		this->_sprite.setScale(0.0f, 0.0f);
	else
		this->_sprite.setScale((float)this->_size.getX() / this->_scale.getX(), (float)this->_size.getY() / this->_scale.getY());
}

std::string const&	SFMLImage::getFile() const
{
	return (this->_filename);
}

Ultra::Color const&	SFMLImage::getColor() const
{
	return (this->_color);
}

Ultra::Vector2D<int> const&	SFMLImage::getPosition() const
{
	return (this->_position);
}

Ultra::Vector2D<size_t> const&	SFMLImage::getSize() const
{
	return (this->_size);
}

void	SFMLImage::initialize()
{
	if (!this->_filename.empty())
	{
		if (!this->_cut)
			this->_texture.loadFromFile(this->_filename);
		else
			this->_texture.loadFromFile(this->_filename,
			sf::IntRect(this->_positionRect.getX(), this->_positionRect.getY(), (int)this->_sizeRect.getX(), (int)this->_sizeRect.getY()));
		this->_texture.setSmooth(true);
		this->_sprite.setTexture(this->_texture);
		sf::FloatRect scale = this->_sprite.getGlobalBounds();
		this->_scale.setX(scale.width);
		this->_scale.setY(scale.height);
	}
}

void	SFMLImage::update()
{

}

void	SFMLImage::unload()
{

}

void	SFMLImage::draw(Engine::IRender* render)
{
	render->draw(&this->_sprite);
}
