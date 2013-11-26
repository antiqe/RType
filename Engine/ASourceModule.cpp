#include "ASourceModule.hpp"

namespace Engine
{
	ASourceModule::ASourceModule()
		: AModule(10)
	{

	}

	ASourceModule::~ASourceModule()
	{

	}

	std::string	const& ASourceModule::getID() const
	{
		return (AModule::SOURCE);
	}
}