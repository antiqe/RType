#ifndef __WIDGET_H__
# define __WIDGET_H__

#include <sys/types.h>
#include <list>
#include <string>

#include "IVisualObject.hpp"
#include "Vector2D.hpp"
#include "Event.hpp"
#include "AEventDispatcher.hpp"
#include "EventListener.hpp"
#include "ICompare.hpp"
#include "IFunctor.hpp"

namespace Engine
{
	class Widget : public AEventDispatcher, public IVisualObject
	{
	protected:
		std::string				_name;
		Ultra::Vector2D<size_t>	_size;
		Ultra::Vector2D<int>	_localPosition;
		Ultra::Vector2D<int>	_globalPosition;
		int						_flag;
		Widget*					_parent;
		std::list<Widget*>		_children;
	public:
		class Compare : public Ultra::ICompare<Widget*>
		{
		private:
			std::string	_name;
		public:
			Compare(std::string const& name);
			virtual ~Compare();

			bool	operator() (Widget* const& widget) const;
		};

		class Functor : public Ultra::IFunctor<Widget*>
		{
		private:
			Event*	_event;
		public:
			Functor(Event* event);
			~Functor();

			void	operator()(Widget* const& widget);
		};

		Widget(std::string const& name);
		virtual ~Widget();

		void	addChild(Widget* widget, size_t n = -1);
		Widget*	removeChild(std::string const& name);
		Widget*	removeChildAt(size_t n);
		void	removeAllChild();

		size_t						getNbChild() const;
		Widget*						getChild(std::string const& name) const;
		Widget*						getChildAt(size_t n) const;
		std::list<Widget*> const&	getAllChild() const;

		Widget*				getParent() const;
		size_t				getWidth() const;
		size_t				getHeight() const;
		int					getLocalX() const;
		int					getLocalY() const;
		int					getX() const;
		int					getY() const;
		std::string const&	getName() const;

		virtual void	setWidth(size_t width);
		virtual void	setHeight(size_t height);
		virtual void	setSize(size_t width, size_t height);
		virtual void	setLocalX(int x);
		virtual void	setLocalY(int y);
		virtual void	setLocalPosition(int x, int y);
		virtual void	setX(int x);
		virtual void	setY(int y);
		virtual void	setPosition(int x, int y);
		void	setName(std::string const& name);

		bool	isDefinedPosition() const;
		bool	isDefinedSize() const;
		bool	isHidden() const;

		void			hide();
		void			show();
		virtual bool	hit(int x, int y) const;
		virtual bool	localHit(int x, int y) const;

		virtual void	dispatchEvent(Event* event) const;
		virtual void	initialize();
		virtual void	update();
		virtual void	unload();
		virtual void	draw(Engine::IRender* render);
	};
}

#endif
