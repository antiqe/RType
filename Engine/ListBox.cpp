#include "ListBox.hpp"
#include "ListBoxCallback.hpp"
#include "VSlider.hpp"
#include "MouseEvent.hpp"
#include "Core.hpp"
#include "ScopeLock.hpp"

//
// CTOR / DTOR
//
/*
namespace Engine
{

	ListBox::ListBox(std::string const &name, std::string const &backgroundFileEven, std::string const &backgroundFileOdd,
		std::string const &backgroundFileFocus, std::string const &sliderBackgroundFile, 
		std::string const &normalCursorFile, std::string const &clickedCursorFile, 
		std::string const &hoverCursorFile, int nbrLine, std::string const &font)
		: Engine::Widget(name)
	{
		this->_textFont = font;
		this->_file[ListBox::EVEN] = backgroundFileEven;
		this->_file[ListBox::ODD] = backgroundFileOdd;
		this->_file[ListBox::FOCUS] = backgroundFileFocus;
		this->_scrollBar = new VSlider(name, sliderBackgroundFile, normalCursorFile, 
			clickedCursorFile, hoverCursorFile, 0, 0);
		this->addChild(this->_scrollBar);
		this->_nbrLine = nbrLine;
		this->_start = this->_content.begin();
		this->setSize(1, 1);
		this->setPosition(0, 0);
		this->_valueSaved = 0;
		this->_focus = -1;
	}

	ListBox::~ListBox()
	{
	}

	//
	// LIFE-CYCLE
	//

	void	ListBox::initialize()
	{
		if ((this->_sourceModule = dynamic_cast<ASourceModule*>(Engine::Core::getInstance()->getModule(Engine::AModule::SOURCE))))
		{
			Ultra::ScopeLock	lock(Engine::Core::getInstance()->access(Engine::AModule::SOURCE));
			for (int i = 0; i < static_cast<int>(ListBox::STATUSSIZE); ++i)
				this->_img[i] = this->_sourceModule->getImage(this->_file[i]);
			this->_drawer = this->_sourceModule->getText(this->_textFont);
		}
		this->addEventListener(Engine::Event::MOUSE, Engine::MouseEvent::MOUSE_WHEEL, &Callback::ListBox::mouseWheel);
		this->addEventListener(Engine::Event::MOUSE, Engine::MouseEvent::LEFT_CLICK, &Callback::ListBox::mouseClick);
		Widget::initialize();
	}

	void	ListBox::update()
	{
		Widget::update();
	}

	void	ListBox::unload()
	{
		this->removeEventListener(Engine::Event::MOUSE, Engine::MouseEvent::MOUSE_WHEEL);
		Widget::unload();
	}

	void	ListBox::draw(Engine::IRender* render)
	{
		std::list<line>::iterator it = this->_start;
		unsigned int i = 0;

		for(; i < this->_nbrLine && it != this->_content.end() ; ++i)
		{
			unsigned int sizeHeight = this->getHeight() / this->_nbrLine;
			Ultra::Vector2D<int> pos = Ultra::Vector2D<int>(this->getX(), this->getY() + (i * (this->getHeight() / this->_nbrLine)));
			int status = (i == (this->_focus - this->_valueSaved) ? ListBox::FOCUS : i % 2);

			this->_img[status]->setSize(Ultra::Vector2D<size_t>(this->getWidth(), sizeHeight));
			this->_img[status]->setPosition(pos);
			this->_img[status]->draw(render);

			this->_drawer->setString(it->first);
			this->_drawer->setColor(status != ListBox::FOCUS ? this->_textColor : this->_focusTextColor);
			this->_drawer->setStyle(this->_textStyle);
			this->_drawer->setSize((size_t)((float)sizeHeight / 1.5));
			pos.setX(pos.getX() + 4);
			this->_drawer->setPosition(pos);
			this->_drawer->draw(render);

			++it;
		}
		for (; i < this->_nbrLine ; ++i)
		{
			unsigned int sizeHeight = this->getHeight() / this->_nbrLine;
			Ultra::Vector2D<int> pos = Ultra::Vector2D<int>(this->getX(), this->getY() + (i * (this->getHeight() / this->_nbrLine)));
			int status = (i == (this->_focus - this->_valueSaved) ? ListBox::FOCUS : i % 2);

			this->_img[status]->setSize(Ultra::Vector2D<size_t>(this->getWidth(), sizeHeight));
			this->_img[status]->setPosition(pos);
			this->_img[status]->draw(render);
		}
		if (this->_nbrLine < this->_content.size())
		{
			if (this->_valueSaved != this->_scrollBar->getValue())
				this->startAt(this->_scrollBar->getValue());
			this->_scrollBar->setSize(this->_scrollWidth, this->getHeight());
			this->_scrollBar->setPosition(this->getX() + this->getWidth(), this->getY());
			this->_scrollBar->draw(render);
		}

	}

	//
	// PUBLIC FUNCTIONS
	//

	void	ListBox::clear()
	{
		this->_content.clear();
		this->_start = this->_content.end();
		this->_scrollBar->setValue(0);
		this->_valueSaved = 0;
		this->_scrollBar->setMax(0);
	}

	void	ListBox::push(std::string const &text, Ultra::Value const &data, bool doScroll)
	{
		if (this->_start == this->_content.end())
		{
			this->_content.push_back(ListBox::line(text, data));
			this->_start = this->_content.begin();
		}
		else
			this->_content.push_back(ListBox::line(text, data));
		if (this->_nbrLine < this->_content.size())
		{
			this->_scrollBar->setMax(this->_scrollBar->getMax() + 1);
			if (doScroll)
				this->scroll(-1);
		}
	}

	void	ListBox::scroll(int delta)
	{
		if (this->_nbrLine < this->_content.size())
			this->_scrollBar->scroll(delta);
	}

	void	ListBox::startAt(int line)
	{
		this->_start = this->_content.begin();
		this->_valueSaved = line;
		this->_scrollBar->setValue(this->_valueSaved);
		for (int i = 0 ; i < line && this->_start != this->_content.end() ; ++i)
			this->_start++;
	}

	void	ListBox::focus(int nbr)
	{
		this->_focus = nbr + this->_valueSaved;
	}

	void	ListBox::unfocus()
	{
		this->_focus = -1;
	}

	//
	// PRIVATE FUNCTIONS
	//

	void	ListBox::incrStart(int val)
	{
		for (int i = 0 ; i < val ; ++i)
		{
			++this->_start;
			++this->_valueSaved;
		}
		this->_scrollBar->setValue(this->_valueSaved);
	}

	void	ListBox::decrStart(int val)
	{
		for (int i = 0 ; i < val ; ++i)
		{
			--this->_start;
			--this->_valueSaved;
		}
		this->_scrollBar->setValue(this->_valueSaved);
	}

	void	ListBox::startAtEnd()
	{
		if (this->_nbrLine < this->_content.size())
		{
			this->_start = this->_content.end();
			for (unsigned int i = 0 ; i < this->_nbrLine ; ++i)
				--this->_start;
			this->_valueSaved = this->_content.size() - this->_nbrLine;
			this->_scrollBar->setValue(this->_valueSaved);
		}
	}

	//
	// SETTER
	//

	void	ListBox::setScrollWidth(unsigned int width)
	{
		this->_scrollWidth = width;
	}

	void	ListBox::setTextFont(std::string const& fontname)
	{
		this->_textFont = fontname;
		Ultra::ScopeLock lock(Engine::Core::getInstance()->access(Engine::AModule::SOURCE));
		this->_drawer = this->_sourceModule->getText(this->_textFont);
	}

	void	ListBox::setTextStyle(unsigned long style)
	{
		this->_textStyle = style;
	}

	void	ListBox::setTextColor(Ultra::Color const& color)
	{
		this->_textColor = color;
	}

	void	ListBox::setFocusTextColor(Ultra::Color const& color)
	{
		this->_focusTextColor = color;
	}

	//
	// GETTER
	//

	unsigned int			ListBox::getScrollWidth() const
	{
		return (this->_scrollWidth);
	}

	std::string const&		ListBox::getTextFont() const
	{
		return (this->_textFont);
	}

	unsigned long			ListBox::getTextStyle() const
	{
		return (this->_textStyle);
	}

	Ultra::Color const&		ListBox::getTextColor() const
	{
		return (this->_textColor);
	}

	Ultra::Color const&		ListBox::getFocusTextColor() const
	{
		return (this->_focusTextColor);
	}

	unsigned int			ListBox::getNbrLine() const
	{
		return (this->_nbrLine);
	}

	std::string	ListBox::getFocusValue() const
	{
		if ((int)this->_focus == -1)
			return ("");
		std::list<line>::iterator it = this->_start;
		for (unsigned int i = 0 ; i < this->_focus - this->_valueSaved && it != this->_content.end() ; ++i)
			++it;
		return (it != this->_content.end() ? it->first : "");
	}

	unsigned int			ListBox::getFocusLine() const
	{
		return (this->_focus);
	}

	Ultra::Value const&		ListBox::getFocusData() const
	{
		return (this->_start->second);
	}
}*/