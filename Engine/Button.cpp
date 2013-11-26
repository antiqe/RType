#include "Button.hpp"
#include "Event.hpp"
#include "MouseEvent.hpp"
#include "ButtonCallback.hpp"
#include "Core.hpp"
#include "ScopeLock.hpp"

namespace Engine
{
	Button::Button(std::string const& name, std::string const& normal, std::string const &clicked, std::string const &hover,
		std::string const &target, Ultra::Color const& color)
		: Engine::Widget(name),
		_lock(false),
		_status(Button::NORMAL),
		_target(target),
		_color(color),
		_stateModule(0),
		_sourceModule(0)
	{
		this->_file[Button::NORMAL] = normal;
		this->_file[Button::CLICKED] = clicked;
		this->_file[Button::HOVER] = hover;
		this->_img[Button::NORMAL] = 0;
		this->_img[Button::CLICKED] = 0;
		this->_img[Button::HOVER] = 0;
		this->setSize(1, 1);
		this->setPosition(0, 0);
	}

	Button::~Button()
	{

	}

	void	Button::initialize()
	{
		this->_stateModule = dynamic_cast<AStateModule*>(Engine::Core::getInstance()->getModule(Engine::AModule::STATE));
		if ((this->_sourceModule = dynamic_cast<ASourceModule*>(Engine::Core::getInstance()->getModule(Engine::AModule::SOURCE))))
		{
			Ultra::ScopeLock	lock(Engine::Core::getInstance()->access(Engine::AModule::SOURCE));
			for (int i = 0; i < static_cast<int>(Button::STATUSSIZE); ++i)
				this->_img[i] = this->_sourceModule->getImage(this->_file[i]);
		}
		this->addEventListener(Engine::Event::MOUSE, Engine::MouseEvent::LEFT_CLICK, &Engine::Callback::Button::mouseClick);
		this->addEventListener(Engine::Event::MOUSE, Engine::MouseEvent::MOUSE_MOVE, &Engine::Callback::Button::mouseOver);
	}

	void	Button::update()
	{
		for (int i = 0; i < static_cast<int>(Button::STATUSSIZE); ++i)
			if (this->_img[i])
				this->_img[i]->update();
	}

	void	Button::unload()
	{
		for (int i = 0; i < static_cast<int>(Button::STATUSSIZE); ++i)
			if (this->_img[i])
				this->_img[i]->unload();
		this->removeEventListener(Engine::Event::MOUSE, Engine::MouseEvent::LEFT_CLICK);
		this->removeEventListener(Engine::Event::MOUSE, Engine::MouseEvent::MOUSE_MOVE);
	}

	void	Button::draw(Engine::IRender* render)
	{
		if (this->_img[this->_status])
		{
			if (this->_lock)
			{
				this->_img[Button::NORMAL]->setColor(Ultra::Color(150, 150, 150, 255));
				this->_img[Button::NORMAL]->setPosition(this->_globalPosition);
				this->_img[Button::NORMAL]->setSize(this->_size);
				this->_img[Button::NORMAL]->draw(render);
			}
			else
			{
				this->_img[this->_status]->setPosition(this->_globalPosition);
				this->_img[this->_status]->setSize(this->_size);
				this->_img[this->_status]->setColor(this->_color);
				this->_img[this->_status]->draw(render);
			}
		}
	}

	void	Button::setStatus(Button::Status status)
	{
		this->_status = status;
	}

	Button::Status	Button::getStatus() const
	{
		return (this->_status);
	}

	void	Button::setTarget(std::string const& target)
	{
		this->_target = target;
	}

	std::string const&	Button::getTarget() const
	{
		return (this->_target);
	}

	void	Button::active()
	{
		if (!this->_target.empty() && this->_stateModule)
		{
			Ultra::ScopeLock		lock(Engine::Core::getInstance()->access(Engine::AModule::STATE));
			this->_stateModule->push(this->_target);
		}
	}

	void	Button::lock()
	{
		this->_lock = true;
	}

	void	Button::unlock()
	{
		this->_lock = false;
	}

	bool	Button::isLock() const
	{
		return (this->_lock);
	}
}