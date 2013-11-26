#include "AModule.hpp"

namespace Engine
{
	std::string const	AModule::EVENT = "event";
	std::string const	AModule::SOUND = "sound";
	std::string const	AModule::RENDER = "render";
	std::string const	AModule::STATE = "state";
	std::string const	AModule::DATA = "data";
	std::string const	AModule::SOURCE = "source";
	std::string const   AModule::NETWORK = "network";
	std::string const	AModule::FACTORY = "factory";

	AModule::Compare::Compare(std::string const& id)
		: _id(id)
	{

	}

	bool	AModule::Compare::operator()(AModule* const& module) const
	{
		return (this->_id == module->getID());
	}

	AModule::AModule(size_t frame)
		: _owner(0), _frame(frame)
	{

	}

	AModule::~AModule()
	{

	}

	bool	AModule::isImportant() const
	{
		return ((int)this->_frame == -1);
	}

	void	AModule::setFrame(size_t frame)
	{
		this->_frame = frame;
	}

	size_t	AModule::getFrame() const
	{
		return (this->_frame);
	}
}