#ifndef _VPARALLAX_H_
# define _VPARALLAX_H_

#include "AParallax.hpp"

namespace Engine
{
	class VParallax : public AParallax
	{
	public:
		VParallax(std::string const& name, std::string const& file, float z = 1.0f, Ultra::Color const& color = Ultra::Color(255));
		~VParallax();

		void	initialize();
		void	update();
		void	unload();
		void	draw(Engine::IRender* render);
		void	scroll();
	};
}

#endif