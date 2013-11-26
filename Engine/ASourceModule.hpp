#ifndef _ASOURCEMODULE_H_
# define _ASOURCEMODULE_H_

# include <string>

# include "AModule.hpp"
# include "IImage.hpp"
# include "IText.hpp"

namespace Engine
{
	class ASourceModule : public AModule
	{
	public:
		ASourceModule();
		virtual ~ASourceModule();

		std::string const&	getID() const;

		virtual IImage*		getImage(std::string const& id) = 0;
		virtual IText*		getText(std::string const& id) = 0;
	};
};

#endif