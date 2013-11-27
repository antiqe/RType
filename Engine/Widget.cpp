#include <iterator>
#include <algorithm>
#include <functional>
#include <iomanip>

#include "Widget.hpp"

namespace Engine
{
	Widget::Compare::Compare(std::string const& name)
		: _name(name)
	{

	}

	Widget::Compare::~Compare()
	{

	}

	bool	Widget::Compare::operator()(Widget* const& widget) const
	{
		return (widget->getName() == this->_name);
	}

	Widget::Functor::Functor(Event* event)
		: _event(event)
	{

	}

	Widget::Functor::~Functor()
	{

	}

	void	Widget::Functor::operator()(Widget* const& widget)
	{
		widget->dispatchEvent(this->_event);
	}

	Widget::Widget(std::string const& name)
		: _name(name),
		_size(Ultra::Vector2D<size_t>(1, 1)),
		_localPosition(Ultra::Vector2D<int>(0, 0)),
		_globalPosition(Ultra::Vector2D<int>(0, 0)),
		_flag(1),
		_parent(0)
	{

	}

	Widget::~Widget()
	{
		this->removeAllChild();
	}

	Widget*	Widget::getParent() const
	{
		return (this->_parent);
	}

	size_t	Widget::getWidth() const
	{
		return (this->_size.getX());
	}

	size_t	Widget::getHeight() const
	{
		return (this->_size.getY());
	}

	int		Widget::getLocalX() const
	{
		return (this->_localPosition.getX());
	}

	int		Widget::getLocalY() const
	{
		return (this->_localPosition.getY());
	}

	int		Widget::getX() const
	{
		return (this->_globalPosition.getX());
	}

	int		Widget::getY() const
	{
		return (this->_globalPosition.getY());
	}

	std::string const&	Widget::getName() const
	{
		return (this->_name);
	}

	void	Widget::setWidth(size_t width)
	{
		this->_flag |= 8;
		if (!width)
			width = 1;
		/*
		for (std::list<Widget*>::iterator it = this->_children.begin(); it != this->_children.end(); ++it)
			(*it)->setWidth(((*it)->getWidth() * width) / this->_size.getX());
		*/
		this->_size.setX(width);
	}

	void	Widget::setHeight(size_t height)
	{
		this->_flag |= 16;
		if (!height)
			height = 1;
		/*
		for (std::list<Widget*>::iterator it = this->_children.begin(); it != this->_children.end(); ++it)
			(*it)->setWidth(((*it)->getHeight() * height) / this->_size.getY());
		*/
		this->_size.setY(height);
	}

	void	Widget::setSize(size_t width, size_t height)
	{
		this->setWidth(width);
		this->setHeight(height);
	}

	void	Widget::setLocalX(int x)
	{
		int	shift = this->_localPosition.getX();

		this->_flag |= 2;
		this->_globalPosition.setX(this->_parent ? this->_parent->getX() + x : x);
		this->_localPosition.setX(x);
		shift = this->_localPosition.getX() - shift;
		for (std::list<Widget*>::iterator it = this->_children.begin(); it != this->_children.end(); ++it)
			if ((((*it)->_flag >> 1) & 1))
				(*it)->setLocalX((*it)->getLocalX() + shift);
	}

	void	Widget::setLocalY(int y)
	{
		int	shift = this->_localPosition.getY();

		this->_flag |= 4;
		this->_globalPosition.setY(this->_parent ? this->_parent->getY() + y : y);
		this->_localPosition.setY(y);
		shift = this->_localPosition.getY() - shift;
		for (std::list<Widget*>::iterator it = this->_children.begin(); it != this->_children.end(); ++it)
			if ((((*it)->_flag >> 2) & 1))
				(*it)->setLocalY((*it)->getLocalY() + shift);
	}

	void	Widget::setLocalPosition(int x, int y)
	{
		this->setLocalX(x);
		this->setLocalY(y);
	}

	void	Widget::setX(int x)
	{
		int	shift = this->_globalPosition.getX();

		this->_flag |= 2;
		this->_localPosition.setX(this->_parent ? x - this->_parent->getX() : x);
		this->_globalPosition.setX(x);
		shift = this->_globalPosition.getX() - shift;
		for (std::list<Widget*>::iterator it = this->_children.begin(); it != this->_children.end(); ++it)
			if ((((*it)->_flag >> 1) & 1))
				(*it)->setX((*it)->getX() + shift);
	}

	void	Widget::setY(int y)
	{
		int	shift = this->_globalPosition.getY();

		this->_flag |= 4;
		this->_localPosition.setY(this->_parent ? y - this->_parent->getY() : y);
		this->_globalPosition.setY(y);
		shift = this->_globalPosition.getY() - shift;
		for (std::list<Widget*>::iterator it = this->_children.begin(); it != this->_children.end(); ++it)
			if ((((*it)->_flag >> 2) & 1))
				(*it)->setY((*it)->getY() + shift);
	}

	void	Widget::setPosition(int x, int y)
	{
		this->setX(x);
		this->setY(y);
	}

	void	Widget::setName(std::string const& name)
	{
		this->_name = name;
	}

	bool	Widget::isDefinedPosition() const
	{
		return (((this->_flag >> 1) & 1) && ((this->_flag >> 2) & 1) ? true : false);
	}

	bool	Widget::isDefinedSize() const
	{
		return (((this->_flag >> 3) & 1) && ((this->_flag >> 4) & 1) ? true : false);
	}

	bool	Widget::isHidden() const
	{
		return (!(this->_flag & 1));
	}

	void	Widget::hide()
	{
		this->_flag ^= 1;
		for (std::list<Widget*>::iterator it = this->_children.begin(); it != this->_children.end(); ++it)
			(*it)->hide();
	}

	void	Widget::show()
	{
		this->_flag |= 1;
		for (std::list<Widget*>::iterator it = this->_children.begin(); it != this->_children.end(); ++it)
			(*it)->show();
	}

	bool	Widget::hit(int x, int y) const
	{
		if (!this->isDefinedPosition() || !this->isDefinedSize())
			return (false);
		return (x >= this->_globalPosition.getX() && x <= (int)(this->_globalPosition.getX() + this->_size.getX()) &&
			y >= this->_globalPosition.getY() && y <= (int)(this->_globalPosition.getY() + this->_size.getY()));
	}

	bool	Widget::localHit(int x, int y) const
	{
		if (!this->isDefinedPosition() || !this->isDefinedSize())
			return (false);
		return (x >= this->_localPosition.getX() && x <= (int)(this->_localPosition.getX() + this->_size.getX()) &&
			y >= this->_localPosition.getY() && y <= (int)(this->_localPosition.getY() + this->_size.getY()));
	}

	void	Widget::addChild(Widget* widget, size_t n)
	{
		if (widget->_parent)
			widget->_parent->removeChild(widget->getName());
		widget->_parent = this;
		widget->setPosition(this->_globalPosition.getX() + widget->getLocalX(), this->_globalPosition.getY() + widget->getLocalY());
		if (n >= this->_children.size())
			this->_children.push_back(widget);
		else if (!n)
			this->_children.push_front(widget);
		else
			this->_children.insert(this->_children.begin(), n, widget);
	}

	Widget*	Widget::removeChild(std::string const& name)
	{
		std::list<Widget*>::iterator	it;
		Widget*							widget = 0;

		it = std::find_if(this->_children.begin(), this->_children.end(), Widget::Compare(name));
		if (it != this->_children.end())
		{
			widget = (*it);
			this->_children.erase(it);
			widget->_parent = 0;
			widget->setPosition(widget->getX(), widget->getY());
		}
		return (widget);
	}

	Widget*	Widget::removeChildAt(size_t n)
	{
		std::list<Widget*>::iterator	it = this->_children.begin();
		Widget*							widget = 0;

		if (n < this->_children.size())
		{
			std::advance(it, n);
			widget = (*it);
			this->_children.erase(it);
			widget->_parent = 0;
			widget->setPosition(widget->getX(), widget->getY());
		}
		return (widget);
	}

	void	Widget::removeAllChild()
	{
		while (!this->_children.empty())
		{
			delete this->_children.front();
			this->_children.pop_front();
		}
	}

	size_t	Widget::getNbChild() const
	{
		return (this->_children.size());
	}

	Widget*	Widget::getChild(std::string const& name) const
	{
		std::list<Widget*>::const_iterator it;

		it = std::find_if(this->_children.begin(), this->_children.end(), Widget::Compare(name));
		return ((it != this->_children.end()) ? *it : 0);
	}

	Widget*	Widget::getChildAt(size_t n) const
	{
		std::list<Widget*>::const_iterator it = this->_children.begin();

		if (n >= this->_children.size())
			return (0);
		std::advance(it, n);
		return (*it);
	}

	std::list<Widget*> const&	Widget::getAllChild() const
	{
		return (this->_children);
	}

	void	Widget::dispatchEvent(Event *event) const
	{
		if (event)
		{
			EventListener::Functor	elFunctor(event->getName(), event->getType(), const_cast<Widget*>(this), event);
			Widget::Functor			widgetFunctor(event);
			if (this->hasEventListener(event->getName(), event->getType()))
				std::for_each(this->_els.begin(), this->_els.end(), elFunctor);
			if (!this->_children.empty())
				std::for_each(this->_children.begin(), this->_children.end(), widgetFunctor);
		}
	}

	void	Widget::initialize()
	{
		std::for_each(this->_children.begin(	), this->_children.end(), std::mem_fun(&Widget::initialize));
	}

	void	Widget::update()
	{
		std::for_each(this->_children.begin(	), this->_children.end(), std::mem_fun(&Widget::update));
	}

	void	Widget::unload()
	{
		std::for_each(this->_children.begin(	), this->_children.end(), std::mem_fun(&Widget::unload));
	}

	void	Widget::draw(IRender*)
	{

	}
}