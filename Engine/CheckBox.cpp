#include "CheckBox.hpp"
#include "Event.hpp"
#include "MouseEvent.hpp"
#include "CheckBoxCallback.hpp"
#include "Core.hpp"
#include "ScopeLock.hpp"

namespace Engine
{
	CheckBox::CheckBox(std::string const&name, std::string const& normalCheckedFile, std::string const &clickedCheckedFile,
		std::string const &hoverCheckedFile, std::string const &normalUncheckedFile,
		std::string const &clickedUncheckedFile, std::string const &hoverUncheckedFile, bool isChecked)
		: Engine::Widget(name), _status(isChecked ? CheckBox::CHECKED_NORMAL : UNCHECKED_NORMAL),
		_stateModule(0), _isChecked(isChecked)
	{
		this->_file[CheckBox::CHECKED_NORMAL] = normalCheckedFile;
		this->_file[CheckBox::CHECKED_CLICKED] = clickedCheckedFile;
		this->_file[CheckBox::CHECKED_HOVER] = hoverCheckedFile;
		this->_file[CheckBox::UNCHECKED_NORMAL] = normalUncheckedFile;
		this->_file[CheckBox::UNCHECKED_CLICKED] = clickedUncheckedFile;
		this->_file[CheckBox::UNCHECKED_HOVER] = hoverUncheckedFile;
		this->setSize(1, 1);
		this->setPosition(0, 0);
	}

	CheckBox::~CheckBox()
	{
	}

	void	CheckBox::initialize()
	{
		this->_stateModule = dynamic_cast<Engine::AStateModule*>(Engine::Core::getInstance()->getModule(Engine::AModule::STATE));
		if ((this->_sourceModule = dynamic_cast<ASourceModule*>(Engine::Core::getInstance()->getModule(Engine::AModule::SOURCE))))
		{
			Ultra::ScopeLock	lock(Engine::Core::getInstance()->access(Engine::AModule::SOURCE));
			for (int i = 0; i < static_cast<int>(CheckBox::STATUSSIZE); ++i)
				this->_img[i] = this->_sourceModule->getImage(this->_file[i]);
		}
		this->addEventListener(Engine::Event::MOUSE, Engine::MouseEvent::LEFT_CLICK, &Callback::CheckBox::mouseClick);
		this->addEventListener(Engine::Event::MOUSE, Engine::MouseEvent::MOUSE_MOVE, &Callback::CheckBox::mouseOver);
	}

	void	CheckBox::update()
	{
	}

	void	CheckBox::unload()
	{
		this->removeEventListener(Engine::Event::MOUSE, Engine::MouseEvent::LEFT_CLICK);
		this->removeEventListener(Engine::Event::MOUSE, Engine::MouseEvent::MOUSE_MOVE);
	}

	void	CheckBox::draw(Engine::IRender* render)
	{
		this->_img[this->_status]->setPosition(this->_globalPosition);
		this->_img[this->_status]->setSize(this->_size);
		this->_img[this->_status]->draw(render);
	}

	void	CheckBox::toggle()
	{
		this->_isChecked = !this->_isChecked;
	}

	void	CheckBox::setStatus(CheckBox::Status status)
	{
		this->_status = status;
	}

	CheckBox::Status	CheckBox::getStatus() const
	{
		return (this->_status);
	}

	bool	CheckBox::isChecked() const
	{
		return (this->_isChecked);
	}
}