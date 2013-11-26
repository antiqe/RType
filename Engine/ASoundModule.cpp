#include "ASoundModule.hpp"

namespace Engine
{
	ASoundModule::ASoundModule()
		: AModule()
	{

	}

	ASoundModule::~ASoundModule()
	{

	}

	std::string	const& ASoundModule::getID() const
	{
		return (AModule::SOUND);
	}
}