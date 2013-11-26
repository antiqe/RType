#include "Callback.hpp"
#include "AModule.hpp"
#include "Core.hpp"
#include "ScopeLock.hpp"
#include "MouseEvent.hpp"
#include "Widget.hpp"
#ifdef _WIN32
#include "WFramer.hpp"
#else
#include "LFramer.hpp"
#endif

namespace Engine
{
	namespace Callback
	{
		void*	run(void* param)
		{
			AModule*		module = reinterpret_cast<AModule*>(param);
			Engine::Core*	core = Engine::Core::getInstance();
#ifdef _WIN32
			Ultra::WFramer	framer(0);
#else
			Ultra::LFramer	framer(0);
#endif

			while (framer.wait())
			{
				{
					Ultra::ScopeLock	lock(core->access());
					if (!core->isRunning())
						break;
				}
				framer.start();
				{
					Ultra::ScopeLock	lock(core->access(module->getID()));
					framer.setFrame(module->getFrame());
					module->update();
				}
				framer.end();
			}
			return (0);
		}

		void	quit(Engine::Widget*, Engine::Event*)
		{
			Engine::Core::getInstance()->stop();
		}

		void	followMouse(Engine::Widget* widget, Engine::Event* event)
		{
			Engine::MouseEvent *mouseEvent = dynamic_cast<Engine::MouseEvent*>(event);
			widget->setPosition(mouseEvent->getX(), mouseEvent->getY());
		}
	}
}