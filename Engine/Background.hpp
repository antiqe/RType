#ifndef _BACKGROUND_H_
# define _BACKGROUND_H_

#include <string>

#include "Widget.hpp"
#include "IImage.hpp"
#include "Color.hpp"
#include "ASourceModule.hpp"

namespace Engine
{
	class Background : public Engine::Widget
	{
	private:
		ASourceModule*	_sourceModule;	
		Ultra::Color	_color;
		std::string		_file;
		Engine::IImage*	_img;
	public:
		Background(std::string const& name, std::string const& file, Ultra::Color const& color = Ultra::Color(255));
		~Background();

		virtual	void	initialize();
		virtual void	update();
		virtual void	unload();
		virtual void	draw(Engine::IRender* render);
	};
}

#endif