#include "TextBox.hpp"
#include "TextBoxCallback.hpp"
#include "KeyboardEvent.hpp"
#include "MouseEvent.hpp"
#include "Core.hpp"
#include "ScopeLock.hpp"
#ifdef _WIN32
#include "WTimer.hpp"
#else
#include "LTimer.hpp"
#endif

namespace Engine
{
	std::map<int, char> const	TextBox::_keyMap = TextBox::buildKeyMap();

	TextBox::TextBox(std::string const& name, std::string const& normal, std::string const &selected, std::string const& hover,
		std::string const& font, size_t limit, std::string const &defaultText, char hide)
		: Engine::Widget(name),
		_limit(limit),
		_hide(hide),
		_lastKey(Engine::Keyboard::Unknown),
		_status(TextBox::NORMAL),
		_cursorTimer(0),
		_keyTimer(0),
		_cursorStatus(false),
		_defaultText(defaultText),
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
		this->_file[TextBox::NORMAL] = normal;
		this->_file[TextBox::SELECTED] = selected;
		this->_file[TextBox::HOVER] = hover;
		this->_img[TextBox::NORMAL] = 0;
		this->_img[TextBox::SELECTED] = 0;
		this->_img[TextBox::HOVER] = 0;
		this->setSize(1, 1);
		this->setPosition(0, 0);
#ifdef _WIN32
		this->_cursorTimer = new Ultra::WTimer();
		this->_keyTimer = new Ultra::WTimer();
#else
		this->_cursorTimer = new Ultra::LTimer();
		this->_keyTimer = new Ultra::LTimer();
#endif
	}

	TextBox::~TextBox()
	{
		delete this->_cursorTimer;
		delete this->_keyTimer;
	}

	void	TextBox::initialize()
	{
		this->_cursorTimer->start();
		if ((this->_sourceModule = dynamic_cast<ASourceModule*>(Engine::Core::getInstance()->getModule(Engine::AModule::SOURCE))))
		{
			Ultra::ScopeLock	lock(Engine::Core::getInstance()->access(Engine::AModule::SOURCE));
			for (int i = 0; i < static_cast<int>(TextBox::STATUSSIZE); ++i)
				this->_img[i] = this->_sourceModule->getImage(this->_file[i]);
			this->_text = this->_sourceModule->getText(this->_fontText);
		}
		this->addEventListener(Engine::Event::MOUSE, Engine::MouseEvent::MOUSE_MOVE, &Callback::TextBox::mouseOver);
		this->addEventListener(Engine::Event::MOUSE, Engine::MouseEvent::LEFT_CLICK, &Callback::TextBox::mouseClick);
		this->addEventListener(Engine::Event::KEYBOARD, Engine::KeyboardEvent::KEY_PRESSED, &Callback::TextBox::touchPressed);
		this->addEventListener(Engine::Event::KEYBOARD, Engine::KeyboardEvent::KEY_RELEASED, &Callback::TextBox::touchReleased);
	}

	void	TextBox::update()
	{
		for (int i = 0; i < static_cast<int>(TextBox::STATUSSIZE); ++i)
			if (this->_img[i])
				this->_img[i]->update();
		if (this->_text)
			this->_text->update();
		if (this->_keyTimer->isTimeOut(0.2f))
		{
			if (this->_lastKey == Engine::Keyboard::BackSpace)
				this->delCharacter();
			else
				this->addCharacter(this->_lastKey);
			this->_keyTimer->restart();
		}
		if (this->_cursorTimer->isTimeOut(0.5f))
		{
			this->_cursorTimer->restart();
			this->_cursorStatus = !this->_cursorStatus;
		}
	}

	void	TextBox::unload()
	{
		for (int i = 0; i < static_cast<int>(TextBox::STATUSSIZE); ++i)
			if (this->_img[i])
				this->_img[i]->unload();
		if (this->_text)
			this->_text->unload();
		this->removeEventListener(Engine::Event::MOUSE, Engine::MouseEvent::MOUSE_MOVE);
		this->removeEventListener(Engine::Event::MOUSE, Engine::MouseEvent::LEFT_CLICK);
		this->removeEventListener(Engine::Event::KEYBOARD, Engine::KeyboardEvent::KEY_PRESSED);
		this->removeEventListener(Engine::Event::KEYBOARD, Engine::KeyboardEvent::KEY_RELEASED);
	}

	void	TextBox::draw(Engine::IRender* render)
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
			if (this->_status != TextBox::SELECTED)
			{
				if (this->_currentText.empty())
					this->_text->setString(this->_defaultText);
				else
					this->_text->setString(this->_hide ? std::string(this->_currentText.size(), this->_hide) : this->_currentText);
			}
			else
			{
				std::string tmp = this->_hide ? std::string(this->_currentText.size(), this->_hide) : this->_currentText;
				this->_text->setString(tmp + (this->_cursorStatus ? "|" : ""));
			}
			this->_text->setSize(this->_sizeText);
			this->_text->setStyle(this->_styleText);
			Ultra::Color colorText = (this->_isLocked ? Ultra::Color(150, 150, 150, 255): this->_colorText);
			this->_text->setColor(colorText);
			this->_text->setPosition(this->_positionText + this->_globalPosition);
			this->_text->draw(render);
		}
	}

	void	TextBox::lock()
	{
		this->_isLocked = true;
	}

	void	TextBox::unlock()
	{
		this->_isLocked = false;
	}

	bool	TextBox::isLocked()
	{
		return (this->_isLocked);
	}

	void	TextBox::setStatus(TextBox::Status type)
	{
		if (type == TextBox::SELECTED)
			this->_cursorTimer->restart();
		else if (type != TextBox::SELECTED && this->_status == TextBox::SELECTED)
		{
			this->_cursorTimer->stop();
			this->_keyTimer->stop();
			if (this->_cursorStatus)
				this->_cursorStatus = false;
			this->setKeyReleased(Engine::Keyboard::Unknown);
		}
		this->_status = type;
	}

	void	TextBox::setDefaultText(std::string const& text)
	{
		this->_defaultText = text;
	}

	void	TextBox::setTextFont(std::string const& fontname)
	{
		this->_fontText = fontname;
		Ultra::ScopeLock	lock(Engine::Core::getInstance()->access(Engine::AModule::SOURCE));
		this->_text = this->_sourceModule->getText(this->_fontText);
	}

	void	TextBox::setTextColor(Ultra::Color const& color)
	{
		this->_colorText = color;
	}

	void	TextBox::setTextSize(size_t size)
	{
		this->_sizeText = size;
	}

	void	TextBox::setTextPosition(int x, int y)
	{
		this->_positionText = Ultra::Vector2D<int>(x, y);
	}

	void	TextBox::setTextStyle(unsigned long style)
	{
		this->_styleText = style;
	}

	TextBox::Status	TextBox::getStatus() const
	{
		return (this->_status);
	}

	std::string const&	TextBox::getDefaultText() const
	{
		return (this->_defaultText);
	}

	std::string const&		TextBox::getTextFont() const
	{
		return (this->_fontText);
	}

	size_t					TextBox::getTextSize() const
	{
		return (this->_sizeText);
	}

	unsigned long			TextBox::getTextStyle() const
	{
		return (this->_styleText);
	}

	Ultra::Vector2D<int>	TextBox::getTextPosition() const
	{
		return (this->_positionText);
	}

	std::string const&		TextBox::getText() const
	{
		return (this->_currentText);
	}

	void	TextBox::addCharacter(Engine::Keyboard::Key c)
	{
		std::map<int, char>::const_iterator it = this->_keyMap.find(c);

		if (it != this->_keyMap.end() && this->_currentText.size() < this->_limit)
			this->_currentText.push_back(it->second);
	}

	void	TextBox::delCharacter()
	{
		if (!this->_currentText.empty())
			this->_currentText = this->_currentText.substr(0, this->_currentText.size() -1);
	}

	void	TextBox::setKeyReleased(Engine::Keyboard::Key c)
	{
		if (c == this->_lastKey)
		{
			this->_lastKey = Engine::Keyboard::Unknown;
			this->_keyTimer->reset();
		}
	}

	void	TextBox::setKeyPressed(Engine::Keyboard::Key c)
	{
		this->_keyTimer->reset();
		this->_keyTimer->start();
		this->_lastKey = c;
	}

	std::map<int, char> const	TextBox::buildKeyMap()
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

	void	TextBox::setHeight(size_t height)
	{
		this->_sizeText = this->_sizeText * height / this->_size.getY();
		Widget::setHeight(height);
	}

	void	TextBox::setText(std::string const &text)
	{
		this->_text->setString(text);
	}
}