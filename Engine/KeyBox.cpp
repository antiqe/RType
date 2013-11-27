#include "KeyBox.hpp"
#include "KeyBoxCallback.hpp"
#include "KeyboardEvent.hpp"
#include "MouseEvent.hpp"
#include "Core.hpp"
#include "ScopeLock.hpp"

namespace Engine
{
	std::map<int, char> const	KeyBox::_keyMap = KeyBox::buildKeyMap();

	KeyBox::KeyBox(std::string const& name, std::string const& normal, std::string const &selected, std::string const& hover,
		std::string const& font, size_t limit)
		: Engine::Widget(name),
		_limit(limit),
		_lastKey(Engine::Keyboard::Unknown),
		_status(KeyBox::NORMAL),
		_currentText(""),
		_positionText(Ultra::Vector2D<int>(0, 0)),
		_fontText(font),
		_colorText(Ultra::Color(0)),
		_sizeText(0),
		_styleText(0),
		_text(0),
		_sourceModule(0),
		_isLocked(false)
	{
		this->_file[KeyBox::NORMAL] = normal;
		this->_file[KeyBox::SELECTED] = selected;
		this->_file[KeyBox::HOVER] = hover;
		this->_img[KeyBox::NORMAL] = 0;
		this->_img[KeyBox::SELECTED] = 0;
		this->_img[KeyBox::HOVER] = 0;
		this->setSize(1, 1);
		this->setPosition(0, 0);
	}

	KeyBox::~KeyBox()
	{
	}

	void	KeyBox::initialize()
	{
		if ((this->_sourceModule = dynamic_cast<ASourceModule*>(Engine::Core::getInstance()->getModule(Engine::AModule::SOURCE))))
		{
			Ultra::ScopeLock	lock(Engine::Core::getInstance()->access(Engine::AModule::SOURCE));
			for (int i = 0; i < static_cast<int>(KeyBox::STATUSSIZE); ++i)
				this->_img[i] = this->_sourceModule->getImage(this->_file[i]);
			this->_text = this->_sourceModule->getText(this->_fontText);
		}
		this->addEventListener(Engine::Event::MOUSE, Engine::MouseEvent::MOUSE_MOVE, &Callback::KeyBox::mouseOver);
		this->addEventListener(Engine::Event::MOUSE, Engine::MouseEvent::LEFT_CLICK, &Callback::KeyBox::mouseClick);
		this->addEventListener(Engine::Event::KEYBOARD, Engine::KeyboardEvent::KEY_PRESSED, &Callback::KeyBox::touchPressed);
		this->addEventListener(Engine::Event::KEYBOARD, Engine::KeyboardEvent::KEY_RELEASED, &Callback::KeyBox::touchReleased);
	}

	void	KeyBox::update()
	{
		for (int i = 0; i < static_cast<int>(KeyBox::STATUSSIZE); ++i)
			if (this->_img[i])
				this->_img[i]->update();
		if (this->_text)
			this->_text->update();
	}

	void	KeyBox::unload()
	{
		for (int i = 0; i < static_cast<int>(KeyBox::STATUSSIZE); ++i)
			if (this->_img[i])
				this->_img[i]->unload();
		if (this->_text)
			this->_text->unload();
		this->removeEventListener(Engine::Event::MOUSE, Engine::MouseEvent::MOUSE_MOVE);
		this->removeEventListener(Engine::Event::MOUSE, Engine::MouseEvent::LEFT_CLICK);
		this->removeEventListener(Engine::Event::KEYBOARD, Engine::KeyboardEvent::KEY_PRESSED);
		this->removeEventListener(Engine::Event::KEYBOARD, Engine::KeyboardEvent::KEY_RELEASED);
	}

	void	KeyBox::draw(Engine::IRender* render)
	{
		if (this->_img[this->_status])
		{
			this->_img[this->_status]->setPosition(this->_globalPosition);
			this->_img[this->_status]->setSize(this->_size);
			this->_img[this->_status]->setColor(this->_isLocked ? Ultra::Color(150, 150, 150, 255) : Ultra::Color(255, 255, 255, 255));
			this->_img[this->_status]->draw(render);
		}
		if (this->_text)
		{
			this->_text->setString(this->_currentText);
			this->_text->setSize(this->_sizeText);
			this->_text->setStyle(this->_styleText);
			Ultra::Color colorText = (this->_isLocked ? Ultra::Color(150, 150, 150, 255): this->_colorText);
			this->_text->setColor(colorText);
			this->_text->setPosition(this->_positionText + this->_globalPosition);
			this->_text->draw(render);
		}
	}

	void	KeyBox::lock()
	{
		this->_isLocked = true;
	}

	void	KeyBox::unlock()
	{
		this->_isLocked = false;
	}

	bool	KeyBox::isLocked()
	{
		return (this->_isLocked);
	}

	void	KeyBox::setStatus(KeyBox::Status type)
	{
		this->_status = type;
	}

	void	KeyBox::setTextFont(std::string const& fontname)
	{
		this->_fontText = fontname;
		Ultra::ScopeLock	lock(Engine::Core::getInstance()->access(Engine::AModule::SOURCE));
		this->_text = this->_sourceModule->getText(this->_fontText);
	}

	void	KeyBox::setTextColor(Ultra::Color const& color)
	{
		this->_colorText = color;
	}

	void	KeyBox::setTextSize(size_t size)
	{
		this->_sizeText = size;
	}

	void	KeyBox::setTextPosition(int x, int y)
	{
		this->_positionText = Ultra::Vector2D<int>(x, y);
	}

	void	KeyBox::setTextStyle(unsigned long style)
	{
		this->_styleText = style;
	}

	KeyBox::Status	KeyBox::getStatus() const
	{
		return (this->_status);
	}

	std::string const&		KeyBox::getTextFont() const
	{
		return (this->_fontText);
	}

	size_t					KeyBox::getTextSize() const
	{
		return (this->_sizeText);
	}

	unsigned long			KeyBox::getTextStyle() const
	{
		return (this->_styleText);
	}

	Ultra::Vector2D<int>	KeyBox::getTextPosition() const
	{
		return (this->_positionText);
	}

	std::string const&		KeyBox::getText() const
	{
		return (this->_currentText);
	}

	void	KeyBox::addCharacter(Engine::Keyboard::Key c)
	{
		std::map<int, char>::const_iterator it = this->_keyMap.find(c);

		if (it != this->_keyMap.end())
		{
			std::ostringstream oss;
			oss << "<" << it->second << ">";
			this->_currentText = oss.str();
		}
	}

	void	KeyBox::delCharacter()
	{
		if (!this->_currentText.empty())
			this->_currentText = this->_currentText.substr(0, this->_currentText.size() -1);
	}

	void	KeyBox::setKeyReleased(Engine::Keyboard::Key c)
	{
		if (c == this->_lastKey)
			this->_lastKey = Engine::Keyboard::Unknown;
	}

	void	KeyBox::setKeyPressed(Engine::Keyboard::Key c)
	{
		this->_lastKey = c;
	}

	std::map<int, char> const	KeyBox::buildKeyMap()
	{
		std::map<int, char>	keyMap;
		int i, k, l;

		for (i = static_cast<int>(Engine::Keyboard::A), k = 'a'; i <= static_cast<int>(Engine::Keyboard::Z); ++i)
			keyMap[i] = k++;
		for (i = static_cast<int>(Engine::Keyboard::Num0), l = static_cast<int>(Engine::Keyboard::Numpad0), k = '0'; k <= '9'; ++k)
		{
			keyMap[i++] = k;
			keyMap[l++] = k;
		}
		keyMap[Engine::Keyboard::Space] = ' ';
		keyMap[Engine::Keyboard::Dash] = '|';
		keyMap[Engine::Keyboard::Period] = '.';
		return (keyMap);
	}

	void	KeyBox::setHeight(size_t height)
	{
		this->_sizeText = this->_sizeText * height / this->_size.getY();
		Widget::setHeight(height);
	}

	void	KeyBox::setText(std::string const &text)
	{
		this->_currentText = text;
		this->_text->setString(text);
	}
}