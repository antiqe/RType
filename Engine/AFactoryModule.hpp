#ifndef _AFACTORYMODULE_H_
# define _AFACTORYMODULE_H_

# include <string>

# include "AModule.hpp"
# include "Factory.hpp"
# include "GameObject.hpp"
# include "Message.hpp"

namespace Engine
{
	class AFactoryModule : public AModule
	{
	public:
		AFactoryModule();
		virtual ~AFactoryModule();

		std::string const&	getID() const;

		virtual Message*			createMessage(unsigned short id) = 0;
		virtual Engine::GameObject*	createGameObject(std::string const& id) = 0;
	};
};

#endif