#ifndef _SFMLIMAGE_H_
# define _SFMLIMAGE_H_

#include <SFML/Graphics.hpp>
#include <string>

#include "Vector2D.hpp"
#include "IImage.hpp"
#include "Color.hpp"

class SFMLImage : public Engine::IImage
{
public:
	bool					_cut;
protected:
	std::string		_filename;
	Ultra::Vector2D<size_t>	_sizeRect;
private:
	Ultra::Vector2D<int>	_positionRect;
protected:
	Ultra::Color			_color;
	Ultra::Vector2D<size_t>	_size;
	Ultra::Vector2D<int>	_position;
	Ultra::Vector2D<float>	_scale;
private:
	sf::Sprite				_sprite;
	sf::Texture				_texture;

public:
	SFMLImage(std::string const& filename);
	SFMLImage(std::string const& filename, int x, int y, size_t width, size_t height);
	~SFMLImage();

	virtual void	setColor(Ultra::Color const& color);
	virtual void	setSize(Ultra::Vector2D<size_t> const &size);
	virtual void	setPosition(Ultra::Vector2D<int> const &position);

	std::string const&				getFile() const;
	Ultra::Color const&				getColor() const;
	Ultra::Vector2D<size_t> const&	getSize() const;
	Ultra::Vector2D<int> const&		getPosition() const;

	virtual void	initialize();
	virtual void	update();
	virtual void	unload();
	virtual void	draw(Engine::IRender* render);

	static std::string const	BACKGROUND;
	static std::string const	TEXTBOX;
	static std::string const	TEXTBOX_HOVER;
	static std::string const	TEXTBOX_SELECTED;
	static std::string const	BUTTON_BACK;
	static std::string const	BUTTON_HOVER_BACK;
	static std::string const	BUTTON_CLICKED_BACK;
	static std::string const	BUTTON_QUIT;
	static std::string const	BUTTON_HOVER_QUIT;
	static std::string const	BUTTON_CLICKED_QUIT;
	static std::string const	BUTTON_LOGIN;
	static std::string const	BUTTON_HOVER_LOGIN;
	static std::string const	BUTTON_CLICKED_LOGIN;
	static std::string const	BUTTON_SETTINGS;
	static std::string const	BUTTON_HOVER_SETTINGS;
	static std::string const	BUTTON_CLICKED_SETTINGS;
	static std::string const	BUTTON_CREATE;
	static std::string const	BUTTON_HOVER_CREATE;
	static std::string const	BUTTON_CLICKED_CREATE;
	static std::string const	BUTTON_JOIN;
	static std::string const	BUTTON_HOVER_JOIN;
	static std::string const	BUTTON_CLICKED_JOIN;
	static std::string const	BUTTON_OK;
	static std::string const	BUTTON_HOVER_OK;
	static std::string const	BUTTON_CLICKED_OK;
	static std::string const	BUTTON_SELECT;
	static std::string const	BUTTON_HOVER_SELECT;
	static std::string const	BUTTON_CLICKED_SELECT;
	static std::string const	BUTTON_REFRESH;
	static std::string const	BUTTON_HOVER_REFRESH;
	static std::string const	BUTTON_CLICKED_REFRESH;
	static std::string const	BUTTON_GO;
	static std::string const	BUTTON_HOVER_GO;
	static std::string const	BUTTON_CLICKED_GO;
	static std::string const	BUTTON_NEXT;
	static std::string const	BUTTON_HOVER_NEXT;
	static std::string const	BUTTON_CLICKED_NEXT;
	static std::string const	BUTTON_PREV;
	static std::string const	BUTTON_HOVER_PREV;
	static std::string const	BUTTON_CLICKED_PREV;
	static std::string const	BUTTON_SEND;
	static std::string const	BUTTON_HOVER_SEND;
	static std::string const	BUTTON_CLICKED_SEND;

	static std::string const	CHECKBOX_CHECKED_NORMAL_PRIVATE;
	static std::string const	CHECKBOX_CHECKED_CLICKED_PRIVATE;
	static std::string const	CHECKBOX_CHECKED_HOVER_PRIVATE;
	static std::string const	CHECKBOX_UNCHECKED_NORMAL_PRIVATE;
	static std::string const	CHECKBOX_UNCHECKED_CLICKED_PRIVATE;
	static std::string const	CHECKBOX_UNCHECKED_HOVER_PRIVATE;
	static std::string const	CHECKBOX_CHECKED_NORMAL_READY;
	static std::string const	CHECKBOX_CHECKED_CLICKED_READY;
	static std::string const	CHECKBOX_CHECKED_HOVER_READY;
	static std::string const	CHECKBOX_UNCHECKED_NORMAL_READY;
	static std::string const	CHECKBOX_UNCHECKED_CLICKED_READY;
	static std::string const	CHECKBOX_UNCHECKED_HOVER_READY;
	static std::string const	CHECKBOX_CHECKED_NORMAL;
	static std::string const	CHECKBOX_CHECKED_CLICKED;
	static std::string const	CHECKBOX_CHECKED_HOVER;
	static std::string const	CHECKBOX_UNCHECKED_NORMAL;
	static std::string const	CHECKBOX_UNCHECKED_CLICKED;
	static std::string const	CHECKBOX_UNCHECKED_HOVER;

	static std::string const	SLIDER;
	static std::string const	HSLIDER;
	static std::string const	SLIDER_CURSOR_NORMAL;
	static std::string const	SLIDER_CURSOR_CLICKED;
	static std::string const	SLIDER_CURSOR_HOVER;
	static std::string const	LISTBOX_EVEN;
	static std::string const	LISTBOX_ODD;
	static std::string const	LISTBOX_FOCUS;
	static std::string const	GAUGE_BACKGROUND;
	static std::string const	GAUGE_FILLED;
	static std::string const	CONNECTION_BACKGROUND;
	static std::string const	PLAY_BACKGROUND;
	static std::string const	JOIN_BACKGROUND;
	static std::string const	ROOM_BACKGROUND;
	static std::string const	SETTINGS_BACKGROUND;

	static std::string const	PLANETE1;
	static std::string const	PLANETE2;
	static std::string const	PLANETE3;
	static std::string const	PLANETE4;

	static std::string const	ARMOR;
	static std::string const	POWER;
	static std::string const	SPEED;

	static std::string const	STARSHIP1NORMAL;
	static std::string const	STARSHIP1UP;
	static std::string const	STARSHIP1DOWN;
};

#endif
