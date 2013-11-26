#ifndef _GOVERNOR_H_
# define _GOVERNOR_H_

#include <map>
#include <string>
#include <list>
#include <functional>

#include "Container.hpp"
#include "IObject.hpp"
#include "IMutex.hpp"
#include "DecoratorThread.hpp"

namespace Engine
{
	class AModule;

	class Governor : public IObject, public Ultra::Container<AModule>
	{
	private:
		std::map<std::string, Ultra::IMutex*>					_mutex;
		std::list<AModule*>										_priority;
		std::list<std::pair<Ultra::DecoratorThread*, AModule*> >	_secondary;

		void	delInternModule(std::string const& id);
		void	delInternModule(AModule* module);
		void	setInternModule(AModule* module);
		void	clearAllInternModule();
	public:
		Governor();
		~Governor();

		AModule*		getModule(std::string const& id) const;
		AModule*		setModule(AModule* module);
		AModule*		delModule(std::string const& id);
		void			clearModules();
		Ultra::IMutex*	access(std::string const& id) const;

		void	initialize();
		void	update();
		void	unload();
		void	draw();
		void	launch();
	};
}

#include "AModule.hpp"

#endif
