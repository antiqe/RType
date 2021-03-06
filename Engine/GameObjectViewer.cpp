#include "GameObjectViewer.hpp"
#include "Event.hpp"
#include "MouseEvent.hpp"
#include "GameObjectViewerCallback.hpp"
#include "Core.hpp"
#include "ScopeLock.hpp"
#include "ARenderComponent.hpp"

namespace Engine
{
	//
	// CTOR / DTOR
	//

	GameObjectViewer::GameObjectViewer(std::string const &name, std::string const &normalNextFile, std::string const &clickedNextFile, 
		std::string const &hoverNextFile, std::string const &normalPrevFile, std::string const &clickedPrevFile, 
		std::string const &hoverPrevFile)
		: Engine::Widget(name)
	{
		this->_next = new Button("next", normalNextFile, clickedNextFile, hoverNextFile);
		this->_prev = new Button("prev", normalPrevFile, clickedPrevFile, hoverPrevFile);
		this->_focus = this->_content.end();
		this->setSize(1, 1);
		this->setPosition(0, 0);
	}

	GameObjectViewer::~GameObjectViewer()
	{
	}

	//
	// LIFE-CYCLE
	//

	void	GameObjectViewer::initialize()
	{
		this->addChild(this->_next);
		this->addChild(this->_prev);
		Widget::initialize();
		this->_sourceModule = dynamic_cast<ASourceModule*>(Engine::Core::getInstance()->getModule(Engine::AModule::SOURCE));
		if ((this->_dataModule = dynamic_cast<ADataModule*>(Engine::Core::getInstance()->getModule(Engine::AModule::DATA))))
		{
			size_t	width = this->_dataModule->getAttr<size_t>("winWidth");
			size_t	height = this->_dataModule->getAttr<size_t>("winHeight");

			this->_next->setSize(width * 2 / 100, height * 2 / 100);
			this->_next->setPosition(width * 8 / 100, height * 3 / 100);
			this->_next->addEventListener(Engine::Event::MOUSE, Engine::MouseEvent::LEFT_CLICK, &Callback::GameObjectViewer::nextOnClick);
			this->_prev->setSize(width * 2 / 100, height * 2 / 100);
			this->_prev->setPosition(width * 0 / 100, height * 3 / 100);
			this->_prev->setLocalPosition(width * 0 / 100, height * 3 / 100);
			this->_prev->addEventListener(Engine::Event::MOUSE, Engine::MouseEvent::LEFT_CLICK, &Callback::GameObjectViewer::prevOnClick);
		}
	}

	void	GameObjectViewer::update()
	{
		Widget::update();
		if (this->_focus != this->_content.end())
			this->_focus->second->update();
	}

	void	GameObjectViewer::unload()
	{
		this->removeEventListener(Engine::Event::MOUSE, Engine::MouseEvent::LEFT_CLICK);
		this->removeEventListener(Engine::Event::MOUSE, Engine::MouseEvent::MOUSE_MOVE);
		Widget::unload();
		this->removeAllChild();
	}

	void	GameObjectViewer::draw(Engine::IRender* render)
	{
		this->_next->draw(render);
		if (this->_focus != this->_content.end())
		{
			ARenderComponent* renderComponent = dynamic_cast<ARenderComponent*>(this->_focus->second->getComponent(AComponent::RENDER));
			renderComponent->initialize();
			this->_img = renderComponent->getImage();
			this->_img->setSize(this->_size);
			this->_img->setPosition(this->_globalPosition);
			this->_img->draw(render);
		}
		this->_prev->draw(render);
	}

	//
	// PUBLIC FUNCTIONS
	//

	void	GameObjectViewer::clear()
	{
		this->_content.clear();
		this->_focus = this->_content.end();
	}

	void	GameObjectViewer::push(std::string const &id, GameObject* gameObject)
	{
		if (this->_content.empty())
		{
			this->_content[id] = gameObject;
			this->_focus = this->_content.begin();
		}
		else
			this->_content[id] = gameObject;
	}

	void	GameObjectViewer::moveTo(std::string const &id)
	{

	}

	void	GameObjectViewer::next()
	{
		if (this->_focus != this->_content.end())
		{
			++this->_focus;
			if (this->_focus == this->_content.end())
				this->_focus = this->_content.begin();
		}
	}

	void	GameObjectViewer::prev()
	{
		if (this->_focus != this->_content.end())
		{
			if (this->_focus == this->_content.begin())
				this->_focus = this->_content.end();
			--this->_focus;
		}
	}

	//
	// GETTER
	//

	std::string const&	GameObjectViewer::getFocusId() const
	{
		return (this->_focus->first);
	}

	GameObject const*	GameObjectViewer::getFocusGameObject() const
	{
		return (this->_focus->second);
	}

	void	GameObjectViewer::lock()
	{
		this->_next->lock();
		this->_prev->lock();
	}

	void	GameObjectViewer::unlock()
	{
		this->_next->unlock();
		this->_prev->unlock();
	}

	bool	GameObjectViewer::isLocked()
	{
		return (this->_next->isLock() && this->_prev->isLock());
	}
}	
