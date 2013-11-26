#include "ARenderModule.hpp"

namespace Engine
{
	ARenderModule::ARenderModule(IRender* render)
		: AModule() , _render(render)
	{

	}

	ARenderModule::~ARenderModule()
	{

	}

	std::string	const&	ARenderModule::getID() const
	{
		return (AModule::RENDER);
	}

	IRender*			ARenderModule::getRender() const
	{
		return (this->_render);
	}
}