#ifndef _BUTTON_H_
# define _BUTTON_H_

#include <string>

#include "Widget.hpp"
#include "IImage.hpp"
#include "Vector2D.hpp"
#include "IRender.hpp"
#include "AStateModule.hpp"
#include "ASourceModule.hpp"

namespace Engine
{
	class Button : public Engine::Widget
	{
	public:
		enum Status
		{
			NORMAL = 0,
			CLICKED,
			HOVER,
			STATUSSIZE
		};
	private:
		bool		_lock;
		Button::Status	_status;
		std::string	_target;
		Ultra::Color	_color;
		AStateModule*	_stateModule;
		ASourceModule*	_sourceModule;
		IImage*			_img[Button::STATUSSIZE];
		std::string		_file[Button::STATUSSIZE];
	public:
		Button(std::string const& name, std::string const& normal, std::string const &clicked, std::string const &hover,
			std::string const &target = "", Ultra::Color const& color = Ultra::Color(255));
		virtual ~Button();

		virtual	void	initialize();
		virtual void	update();
		virtual void	unload();
		virtual void	draw(Engine::IRender* render);

		virtual void	active();

		void	lock();
		void	unlock();
		bool	isLock() const;

		void	setStatus(Button::Status status);
		void	setTarget(std::string const& target);

		Button::Status		getStatus() const;
		std::string const&	getTarget() const;
	};
}

#endif
