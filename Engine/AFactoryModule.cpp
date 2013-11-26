#include "AFactoryModule.hpp"

namespace Engine
{
	AFactoryModule::AFactoryModule()
		: AModule(10)
	{

	}

	AFactoryModule::~AFactoryModule()
	{

	}

	std::string	const& AFactoryModule::getID() const
	{
		return (AModule::FACTORY);
	}
}