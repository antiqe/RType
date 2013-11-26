#ifndef _CORE_H_
# define _CORE_H_

#include <exception>

#include "AFramer.hpp"
#include "Governor.hpp"
#include "AModule.hpp"
#include "IMutex.hpp"
#include "AFactoryModule.hpp"
#include "MessageFactory.hpp"

namespace Engine
{
	class Core
	{
	private:
		bool				_isRunning;
		Ultra::AFramer*		_framer;
		Engine::Governor	_governor;
		Ultra::IMutex*		_mutex;

		static Core*		_instance;

		class Exception : public std::exception
		{
		public:
			Exception() throw() {}
			virtual ~Exception() throw() {}
		};

		Core();
	public:
		~Core();

		void	run();
		void	stop();
		bool	isRunning() const;

		void	setFrame(size_t frame);
		size_t	getFrame() const;

		static Core*	getInstance();
		static void		kill();

		static Ultra::Factory<Message, unsigned short>*		messagefactory;
		static Ultra::Factory<GameObject>*					gameObjectFactory;

		AModule*		getModule(std::string const& id) const;
		AModule*		setModule(AModule* module);
		AModule*		delModule(std::string const& id);
		void			clearModules();

		Ultra::IMutex*	access(std::string const& id) const;
		Ultra::IMutex*	access() const;
	};
}

#endif