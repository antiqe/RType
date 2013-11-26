#include <algorithm>
#include <functional>

#include "Governor.hpp"
#include "ARenderModule.hpp"
#include "ScopeLock.hpp"
#include "Callback.hpp"
#ifdef _WIN32
#include "WMutex.hpp"
#else
#include "LMutex.hpp"
#endif

namespace Engine
{
	Governor::Governor()
	{

	}

	Governor::~Governor()
	{
		this->clearModules();
	}

	void	Governor::setInternModule(AModule* module)
	{
		if (module->isImportant())
			this->_priority.push_front(module);
		else
			this->_secondary.push_front(std::pair<Ultra::DecoratorThread*, AModule*>(new Ultra::DecoratorThread(), module));
	}

	void	Governor::delInternModule(AModule* module)
	{
		if (module->isImportant())
		{
			std::list<AModule*>::iterator it;
			it = std::find_if(this->_priority.begin(), this->_priority.end(), AModule::Compare(module->getID()));
			this->_priority.erase(it);
		}
		else
		{
			std::list<std::pair<Ultra::DecoratorThread*, AModule*> >::iterator it = this->_secondary.begin();
			for (; it != this->_secondary.end(); ++it)
				if (it->second->getID() == module->getID())
				{
					delete it->first;
					this->_secondary.erase(it);
					break;
				}
		}
	}

	void	Governor::delInternModule(std::string const& id)
	{
		this->delInternModule(this->getContent(id));
	}

	AModule*	Governor::getModule(std::string const& id) const
	{
		return (this->getContent(id));
	}

	AModule*	Governor::setModule(AModule* module)
	{
		if (!module)
			return (0);
		AModule*	old = Ultra::Container<AModule>::setContent(module);
		if (old)
		{
			old->_owner = 0;
			this->delInternModule(old);
		}
		module->_owner = this;
		this->setInternModule(module);
#ifdef _WIN32
		this->_mutex[module->getID()] = new Ultra::WMutex;
#else
		this->_mutex[module->getID()] = new Ultra::LMutex;
#endif
		return (old);
	}

	AModule*	Governor::delModule(std::string const& id)
	{
		std::map<std::string, Ultra::IMutex*>::iterator it = this->_mutex.find(id);

		if (it != this->_mutex.end())
		{
			delete it->second;
			this->_mutex.erase(it);
		}
		this->delInternModule(id);
		return (this->delContent(id));
	}

	void	Governor::clearAllInternModule()
	{
		std::list<std::pair<Ultra::DecoratorThread*, AModule*> >::iterator it = this->_secondary.begin();

		for (; it != this->_secondary.end(); ++it)
			delete it->first;
		this->_priority = std::list<AModule*>();
		this->_secondary = std::list<std::pair<Ultra::DecoratorThread*, AModule*> >();
	}

	void	Governor::clearModules()
	{
		for (std::map<std::string, Ultra::IMutex*>::iterator it = this->_mutex.begin(); it != this->_mutex.end(); ++it)
			delete it->second;
		this->_mutex = std::map<std::string, Ultra::IMutex*>();
		this->clearAllInternModule();
		this->clearContents();
	}

	void	Governor::initialize()
	{
		std::for_each(this->_contents.begin(), this->_contents.end(), std::mem_fun(&AModule::initialize));
	}

	void	Governor::update()
	{
		for (std::list<AModule*>::iterator it = this->_priority.begin(); it != this->_priority.end(); ++it)
		{
			Ultra::ScopeLock	lock(this->access((*it)->getID()));
			(*it)->update();
		}
	}

	void	Governor::unload()
	{
		for (std::list<std::pair<Ultra::DecoratorThread*, AModule*> >::iterator it = this->_secondary.begin(); it != this->_secondary.end(); ++it)
			it->first->wait();
		std::for_each(this->_contents.begin(), this->_contents.end(), std::mem_fun(&AModule::unload));
	}

	void	Governor::draw()
	{
		ARenderModule*	renderModule = dynamic_cast<ARenderModule*>(this->getContent(AModule::RENDER));

		if (renderModule)
		{
			Ultra::ScopeLock	lock(this->access(AModule::RENDER));
			renderModule->draw();
		}
	}

	void	Governor::launch()
	{
		for (std::list<std::pair<Ultra::DecoratorThread*, AModule*> >::iterator it = this->_secondary.begin(); it != this->_secondary.end(); ++it)
			it->first->create(&Callback::run, it->second);
	}

	Ultra::IMutex*	Governor::access(std::string const& id) const
	{
		std::map<std::string, Ultra::IMutex*>::const_iterator it = this->_mutex.find(id);

		return (it == this->_mutex.end() ? 0 : it->second);
	}
}
