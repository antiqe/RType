#ifndef _ASTATEMODULE_H_
# define _ASTATEMODULE_H_

# include <string>
# include <map>
# include <stack>

# include "AModule.hpp"
# include "AState.hpp"

namespace Engine
{
	class AStateModule : public AModule
	{
	protected:
		std::string						_mainName;					
		std::map<std::string, AState*>	_statePool;
		std::stack<AState*>				_stateStack;
	public:
		AStateModule(std::string const& mainName);
		virtual ~AStateModule();

		std::string const&	getID() const;

		void	push(std::string const& name);
		void	popTo(std::string const& name);
		void	pop();
		void	backToMain();
		AState*	top() const;
		AState*	getState(std::string const& name) const;
	};
};

#endif