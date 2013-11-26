#include "Core.hpp"
#include "ScopeLock.hpp"
#ifdef _WIN32
#include "WFramer.hpp"
#include "WMutex.hpp"
#else
#include "LFramer.hpp"
#include "LMutex.hpp"
#endif

namespace Engine
{
	Core*			Core::_instance = 0;

	Ultra::Factory<Message, unsigned short>*	Engine::Core::messagefactory = 0;
	Ultra::Factory<GameObject>*					Engine::Core::gameObjectFactory = 0;			

	Core::Core()
		: _isRunning(false)
	{
#ifdef _WIN32
		this->_framer = new Ultra::WFramer(60);
		this->_mutex = new Ultra::WMutex;
#else
		this->_framer = new Ultra::LFramer(60);
		this->_mutex = new Ultra::LMutex;
#endif
	}

	Core::~Core()
	{
		delete this->_framer;
	}

	void	Core::run()
	{
		this->_isRunning = true;
		try
		{
			this->_governor.initialize();
			this->_governor.launch();
			while (this->_framer->wait())
			{
				this->_framer->start();
				this->_governor.update();
				this->_governor.draw();
				this->_framer->end();
			}
		}
		catch (Core::Exception)
		{
			this->_governor.unload();
		}
	}

	bool	Core::isRunning() const
	{
		return (this->_isRunning);
	}

	void	Core::stop()
	{
		Ultra::ScopeLock	lock(this->_mutex);
		this->_isRunning = false;
		throw Core::Exception();
	}

	void	Core::setFrame(size_t frame)
	{
		this->_framer->setFrame(frame);
	}

	size_t	Core::getFrame() const
	{
		return (this->_framer->getFrame());
	}


	Core*	Core::getInstance()
	{
		if (!Core::_instance)
			Core::_instance = new Core();
		return (Core::_instance);
	}

	void	Core::kill()
	{
		if (Core::_instance)
		{
			if (Core::_instance->isRunning())
				Core::_instance->stop();
			delete Core::_instance;
			Core::_instance = 0;
		}
	}

	AModule*	Core::getModule(std::string const& id) const
	{
		return (this->_governor.getContent(id));
	}

	AModule*	Core::setModule(AModule* module)
	{
		return (this->_governor.setModule(module));
	}

	AModule*	Core::delModule(std::string const& id)
	{
		return (this->_governor.delModule(id));
	}

	void	Core::clearModules()
	{
		this->_governor.clearContents();
	}

	Ultra::IMutex*	Core::access(std::string const& id) const
	{
		return (this->_governor.access(id));
	}

	Ultra::IMutex*	Core::access() const
	{
		return (this->_mutex);
	}
}
