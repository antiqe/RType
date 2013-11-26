#include "AStateModule.hpp"
#include "Exception.hpp"

namespace Engine
{
	AStateModule::AStateModule(std::string const& mainName)
		: AModule(60), _mainName(mainName)
	{

	}

	AStateModule::~AStateModule()
	{

	}

	std::string	const& AStateModule::getID() const
	{
		return (AModule::STATE);
	}

	void	AStateModule::push(std::string const& name)
	{
		if (this->_statePool.find(name) != this->_statePool.end())
		{
			this->_stateStack.push(this->_statePool[name]);
			this->_statePool[name]->reset();
		}
	}

	void	AStateModule::popTo(std::string const& name)
	{
		if (this->_statePool.find(name) != this->_statePool.end())
		{
			AState *target = this->_statePool[name];
			while (this->_stateStack.top() != target)
				this->_stateStack.pop();
			target->reload();
		}
	}

	void	AStateModule::pop()
	{
		this->_stateStack.pop();
		if (!this->_stateStack.empty())
			this->_stateStack.top()->reload();
	}

	void AStateModule::backToMain()
	{
		this->popTo(this->_mainName);
	}

	AState*	AStateModule::top() const
	{
		return (this->_stateStack.empty() ? 0 : this->_stateStack.top());
	}

	AState*	AStateModule::getState(std::string const& name) const
	{
		std::map<std::string, AState*>::const_iterator it = this->_statePool.find(name);

		if (it != this->_statePool.end())
			return (it->second);
		return (0);
	}
}
