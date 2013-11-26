#ifndef _V_GAUGE_H_
# define _V_GAUGE_H_

#include "AGauge.hpp"

namespace Engine
{
	class VGauge : public AGauge
	{
	public:
		VGauge(std::string const &name, std::string const &backgroundFile, std::string const &filledFile, int percent = 0);
		~VGauge();

		void	draw(Engine::IRender* render);

	};
}

#endif