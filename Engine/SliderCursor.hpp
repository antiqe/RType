#ifndef _SLIDER_CURSOR_H_
# define _SLIDER_CURSOR_H_

#include <string>

#include "Widget.hpp"
#include "IImage.hpp"
#include "Vector2D.hpp"
#include "IRender.hpp"
#include "AStateModule.hpp"
#include "ASourceModule.hpp"

namespace Engine
{
	class SliderCursor : public Engine::Widget
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
		SliderCursor::Status	_status;
		Engine::AStateModule*	_stateModule;
		ASourceModule*			_sourceModule;
		Engine::IImage*			_img[SliderCursor::STATUSSIZE];
		std::string				_file[SliderCursor::STATUSSIZE];

		Engine::Callback::EventFunction _moveCallback;

	public:
		SliderCursor(std::string const &name, std::string const &normalFile, std::string const &clickedFile,
			std::string const &hoverFile, Engine::Callback::EventFunction moveCallback);
		virtual ~SliderCursor();

		virtual	void	initialize();
		virtual void	update();
		virtual void	unload();
		virtual void	draw(Engine::IRender* render);

		void					setStatus(SliderCursor::Status status);
		SliderCursor::Status	getStatus() const;
	};
}

#endif
