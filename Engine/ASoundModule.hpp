#ifndef _ASOUNDMODULE_H_
# define _ASOUNDMODULE_H_

# include <string>

# include "AModule.hpp"

namespace Engine
{
	class ASoundModule : public AModule
	{
	public:
		ASoundModule();
		virtual ~ASoundModule();

		std::string const&	getID() const;
	};
};

#endif