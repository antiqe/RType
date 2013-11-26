#include "AEventModule.hpp"

namespace Engine
{
	AEventModule::AEventModule()
		: AModule()
	{

	}

	AEventModule::~AEventModule()
	{

	}

	std::string	const& AEventModule::getID() const
	{
		return (AModule::EVENT);
	}
}