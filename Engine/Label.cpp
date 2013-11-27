#include "Label.hpp"
#include "Core.hpp"
#include "ScopeLock.hpp"

//
// CTOR / DTOR
//

namespace Engine
{
	Label::Label(std::string const& name, std::string const& font, std::string const &content)
		: Engine::Widget(name), _content(content), _fontText(font)
	{
	}

	Label::~Label()
	{
	}

	//
	// LIFE-CYCLE
	//

	void	Label::initialize()
	{
		if ((this->_sourceModule = dynamic_cast<ASourceModule*>(Engine::Core::getInstance()->getModule(Engine::AModule::SOURCE))))
		{	
			Ultra::ScopeLock lock(Engine::Core::getInstance()->access(Engine::AModule::SOURCE));
			this->_text = this->_sourceModule->getText(this->_fontText);
		}
	}

	void	Label::update()
	{
	}

	void	Label::unload()
	{
	}

	void	Label::draw(Engine::IRender* render)
	{
		if (this->_text)
		{
			this->_text->setSize(this->_sizeText);
			this->_text->setStyle(this->_styleText);
			this->_text->setColor(this->_colorText);
			this->_text->setPosition(this->_positionText + this->_globalPosition);
			this->_text->setString(this->_content);
			this->_text->draw(render);
		}
	}

	//
	// SETTER
	//

	void	Label::setText(std::string const &text)
	{
		this->_content = text;
	}

	void	Label::setContent(std::string const& text)
	{
		this->_content = text;
	}

	void	Label::setTextFont(std::string const& fontname)
	{
		this->_fontText = fontname;
		Ultra::ScopeLock lock(Engine::Core::getInstance()->access(Engine::AModule::SOURCE));
		this->_text = this->_sourceModule->getText(this->_fontText);
	}

	void	Label::setTextColor(Ultra::Color const& color)
	{
		this->_colorText = color;
	}

	void	Label::setTextSize(size_t size)
	{
		this->_sizeText = size;
	}

	void	Label::setTextPosition(int x, int y)
	{
		this->_positionText = Ultra::Vector2D<int>(x, y);
	}

	void	Label::setTextStyle(unsigned long style)
	{
		this->_styleText = style;
	}

	//
	// GETTER
	//

	std::string const&	Label::getContent() const
	{
		return (this->_content);
	}

	std::string const&		Label::getTextFont() const
	{
		return (this->_fontText);
	}

	size_t					Label::getTextSize() const
	{
		return (this->_sizeText);
	}

	unsigned long			Label::getTextStyle() const
	{
		return (this->_styleText);
	}

	Ultra::Vector2D<int>	Label::getTextPosition() const
	{
		return (this->_positionText);
	}
}