#include "SliderCursor.hpp"
#include "Event.hpp"
#include "MouseEvent.hpp"
#include "SliderCursorCallback.hpp"
#include "Core.hpp"
#include "ScopeLock.hpp"

namespace Engine
{
	SliderCursor::SliderCursor(std::string const &name, std::string const &normalFile, std::string const &clickedFile,
		std::string const &hoverFile, Engine::Callback::EventFunction moveCallback)
		: Engine::Widget(name), _status(SliderCursor::NORMAL), _stateModule(0)
	{
		this->_file[SliderCursor::NORMAL] = normalFile;
		this->_file[SliderCursor::CLICKED] = clickedFile;
		this->_file[SliderCursor::HOVER] = hoverFile;
		this->_moveCallback = moveCallback;
		this->setSize(1, 1);
		this->setPosition(0, 0);
	}

	SliderCursor::~SliderCursor()
	{
	}

	void	SliderCursor::initialize()
	{
		this->_stateModule = dynamic_cast<Engine::AStateModule*>(Engine::Core::getInstance()->getModule(Engine::AModule::STATE));
		if ((this->_sourceModule = dynamic_cast<ASourceModule*>(Engine::Core::getInstance()->getModule(Engine::AModule::SOURCE))))
		{
			Ultra::ScopeLock	lock(Engine::Core::getInstance()->access(Engine::AModule::SOURCE));
			for (int i = 0; i < static_cast<int>(SliderCursor::STATUSSIZE); ++i)
				this->_img[i] = this->_sourceModule->getImage(this->_file[i]);
		}
		this->addEventListener(Engine::Event::MOUSE, Engine::MouseEvent::LEFT_CLICK, &Callback::SliderCursor::mouseClick);
		this->addEventListener(Engine::Event::MOUSE, Engine::MouseEvent::MOUSE_MOVE, &Callback::SliderCursor::mouseOver);
		this->addEventListener(Engine::Event::MOUSE, Engine::MouseEvent::MOUSE_MOVE, this->_moveCallback);
	}

	void	SliderCursor::update()
	{
	}

	void	SliderCursor::unload()
	{
		this->removeEventListener(Engine::Event::MOUSE, Engine::MouseEvent::LEFT_CLICK);
		this->removeEventListener(Engine::Event::MOUSE, Engine::MouseEvent::MOUSE_MOVE);
		this->removeEventListener(Engine::Event::MOUSE, Engine::MouseEvent::MOUSE_MOVE);
	}

	void	SliderCursor::draw(Engine::IRender* render)
	{
		this->_img[this->_status]->setPosition(this->_globalPosition);
		this->_img[this->_status]->setSize(this->_size);
		this->_img[this->_status]->draw(render);
	}

	void	SliderCursor::setStatus(SliderCursor::Status status)
	{
		this->_status = status;
	}

	SliderCursor::Status	SliderCursor::getStatus() const
	{
		return (this->_status);
	}
}