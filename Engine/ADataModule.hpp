#ifndef _ADATAMODULE_H_
# define _ADATAMODULE_H_

# include <string>

# include "AModule.hpp"
# include "Attr.hpp"

namespace Engine
{
	class ADataModule : public AModule, public Ultra::Attr
	{
	protected:
		std::string _filename;
	public:
		ADataModule(std::string const& filename);
		virtual ~ADataModule();

		std::string const&	getID() const;
	};
};

#endif