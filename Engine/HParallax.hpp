#ifndef _HPARALLAX_H_
# define _HPARALLAX_H_

#include "AParallax.hpp"

namespace Engine
{
	class HParallax : public AParallax
	{
	public:
		HParallax(std::string const& name, std::string const& file, float z = 1.0f, Ultra::Color const& color = Ultra::Color(255));
		~HParallax();

		void	initialize();
		void	update();
		void	unload();
		void	draw(Engine::IRender* render);
		void	scroll();
	};
}

#endif