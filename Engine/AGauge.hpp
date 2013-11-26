#ifndef _A_GAUGE_H_
# define _A_GAUGE_H_

#include <string>

#include "Widget.hpp"
#include "IImage.hpp"
#include "Vector2D.hpp"
#include "IRender.hpp"
#include "ASourceModule.hpp"

namespace Engine
{
	class AGauge : public Engine::Widget
	{
	protected:
		ASourceModule*	_sourceModule;
		int				_percent;
		std::string		_bgFile;
		std::string		_filledFile;
		IImage*			_bgImg;
		IImage*			_filledImg;

	public:
		AGauge(std::string const &name, std::string const &backgroundFile, std::string const &filledFile, int percent = 0);
		virtual ~AGauge();

		virtual	void	initialize();
		virtual void	update();
		virtual void	unload();
		virtual void	draw(Engine::IRender* render) = 0;

		int				getPercent() const;
		void			setPercent(int percent);
		void			setFilledImg(std::string const &filledFile);
	};
}

#endif