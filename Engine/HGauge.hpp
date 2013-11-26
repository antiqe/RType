#ifndef _H_GAUGE_H_
# define _H_GAUGE_H_

#include "AGauge.hpp"

namespace Engine
{
	class HGauge : public AGauge
	{
	public:
		HGauge(std::string const &name, std::string const &backgroundFile, std::string const &filledFile, int percent = 0);
		~HGauge();

		void	draw(Engine::IRender* render);

	};
}

#endif