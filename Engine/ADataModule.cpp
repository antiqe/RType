#include "ADataModule.hpp"

namespace Engine
{
	ADataModule::ADataModule(std::string const& filename)
		: AModule(10), Attr(), _filename(filename)
	{

	}

	ADataModule::~ADataModule()
	{

	}

	std::string	const& ADataModule::getID() const
	{
		return (AModule::DATA);
	}
}