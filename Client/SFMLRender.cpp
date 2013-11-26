#include "SFMLRender.hpp"

SFMLRender::SFMLRender()
	: _window(0), _title(""), _mode(0)
{

}

SFMLRender::~SFMLRender()
{
	this->close();
}

Engine::Event*	SFMLRender::pollEvent()
{
	if (this->isOpen())
	{
		sf::Event	event;
		if (this->_window->pollEvent(event))
			return (this->_input.createEvent(event));
	}
	return (0);
}

void	SFMLRender::display()
{
	if (this->isOpen())
		this->_window->display();
}

void	SFMLRender::clear()
{
	if (this->isOpen())
		this->_window->clear();
}

void	SFMLRender::open(size_t width, size_t height, std::string const& title, unsigned long mode)
{
	if (!this->isOpen())
	{
		this->_window = new sf::RenderWindow(sf::VideoMode(width, height), title.c_str(), mode);
		this->_window->setVerticalSyncEnabled(true);
		this->_window->setKeyRepeatEnabled(false);
		this->_title = title;
		this->_mode = mode;
	}
}

void	SFMLRender::close()
{
	if (this->isOpen())
	{
		this->_window->close();
		delete this->_window;
		this->_window = 0;
		this->_title = "";
		this->_mode = 0;
	}	
}

bool	SFMLRender::isOpen() const
{
	return (this->_window && this->_window->isOpen());
}

int		SFMLRender::getX() const
{
	return (this->isOpen() ? this->_window->getPosition().x : 0);
}

int		SFMLRender::getY() const
{
	return (this->isOpen() ? this->_window->getPosition().y : 0);
}

Ultra::Vector2D<int>	SFMLRender::getPosition() const
{
	return (this->isOpen() ? Ultra::Vector2D<int>(this->_window->getPosition().x, this->_window->getPosition().y) : Ultra::Vector2D<int>(0, 0));
}

size_t	SFMLRender::getWidth() const
{
	return (this->isOpen() ? this->_window->getSize().x : 0);
}

size_t	SFMLRender::getHeight() const
{
	return (this->isOpen() ? this->_window->getSize().y : 0);
}

Ultra::Vector2D<size_t>	SFMLRender::getSize() const
{
	return (this->isOpen() ? Ultra::Vector2D<size_t>(this->_window->getSize().x, this->_window->getSize().y) : Ultra::Vector2D<size_t>(0, 0));
}

std::string const&	SFMLRender::getTitle() const
{
	return (this->_title);
}

unsigned long	SFMLRender::getMode() const
{
	return (this->_mode);
}

void	SFMLRender::setX(int x)
{
	if (this->isOpen())
		this->_window->setPosition(sf::Vector2i(x, this->_window->getPosition().y));
}

void	SFMLRender::setY(int y)
{
	if (this->isOpen())
		this->_window->setPosition(sf::Vector2i(this->_window->getPosition().x, y));	
}

void	SFMLRender::setPosition(Ultra::Vector2D<int> const& position)
{
	if (this->isOpen())
		this->_window->setPosition(sf::Vector2i(position.getX(), position.getY()));	
}

void	SFMLRender::setPosition(int x, int y)
{
	if (this->isOpen())
		this->_window->setPosition(sf::Vector2i(x, y));	
}

void	SFMLRender::setWidth(size_t width)
{
	if (this->isOpen())
		this->_window->setSize(sf::Vector2u(width, this->_window->getSize().y));
}

void	SFMLRender::setHeight(size_t height)
{
	if (this->isOpen())
		this->_window->setSize(sf::Vector2u(this->_window->getSize().x, height));
}

void	SFMLRender::setSize(Ultra::Vector2D<size_t> const& size)
{
	if (this->isOpen())
		this->_window->setSize(sf::Vector2u(size.getX(), size.getY()));
}

void	SFMLRender::setSize(size_t width, size_t height)
{
	if (this->isOpen())
		this->_window->setSize(sf::Vector2u(width, height));
}

void	SFMLRender::setTitle(std::string const& title)
{
	if (this->isOpen())
	{
		this->_title = title;
		this->_window->setTitle(title.c_str());
	}
}

void	SFMLRender::setMode(unsigned long mode)
{
	if (this->isOpen())
	{
		sf::Vector2u	size = this->_window->getSize();
		sf::Vector2i	position = this->_window->getPosition();
		this->_mode = mode;
		this->_window->close();
		delete this->_window;
		this->_window = new sf::RenderWindow(sf::VideoMode(size.x, size.y), this->_title.c_str(), mode);
		this->_window->setPosition(position);
		this->_window->setVerticalSyncEnabled(true);
		this->_window->setKeyRepeatEnabled(false);
	}
}

void	SFMLRender::draw(void* drawable)
{
	this->_window->draw(*reinterpret_cast<sf::Drawable*>(drawable));
}