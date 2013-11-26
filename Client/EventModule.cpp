#include "EventModule.hpp"
#include "Singleton.hpp"
#include "Core.hpp"
#include "ScopeLock.hpp"

EventModule::EventModule()
	: Engine::AEventModule(), _stateModule(0), _renderModule(0)
{

}

EventModule::~EventModule()
{

}

void	EventModule::initialize()
{
	if (this->_owner)
	{
		this->_stateModule = dynamic_cast<StateModule*>(this->_owner->getModule(Engine::AModule::STATE));
		this->_renderModule = dynamic_cast<RenderModule*>(this->_owner->getModule(Engine::AModule::RENDER));
	}
}

void	EventModule::update()
{
	if (this->_renderModule)
	{
		{
			Ultra::ScopeLock	lock(Engine::Core::getInstance()->access(AModule::RENDER));
			Engine::IRender*	render = this->_renderModule->getRender();
			Engine::Event*		event;
			while ((event = render->pollEvent()))
				this->_eventQueue.push(event);
		}
		if (!this->_eventQueue.empty())
		{
			Ultra::ScopeLock	lock(Engine::Core::getInstance()->access(AModule::STATE));
			Engine::AState*		state = !this->_stateModule ? 0 : this->_stateModule->top();
			while (!this->_eventQueue.empty())
			{
				if (state)
					state->dispatchEvent(this->_eventQueue.front());
				delete this->_eventQueue.front();
				this->_eventQueue.pop();
			}
		}
	}
}

void	EventModule::unload()
{
	while (!this->_eventQueue.empty())
	{
		delete this->_eventQueue.front();
		this->_eventQueue.pop();
	}
}
