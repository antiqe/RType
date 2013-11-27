#include "Configuration.hpp"
#include "IInput.hpp"

int					Configuration::X = 0;
int					Configuration::Y = 0;
float				Configuration::SCALE = 0.8f;
unsigned long		Configuration::MODE  = 5;
std::string const	Configuration::NAME = "RTYPE";
int					Configuration::GLOBAL_SOUND = 100;
int					Configuration::AMBIENT_SOUND = 30;
int					Configuration::EFFECT_SOUND = 50;
int					Configuration::UP = (int)Engine::Keyboard::Up;
int					Configuration::DOWN = (int)Engine::Keyboard::Down;
int					Configuration::LEFT = (int)Engine::Keyboard::Left;
int					Configuration::RIGHT = (int)Engine::Keyboard::Right;
int					Configuration::SHOOT = (int)Engine::Keyboard::Space;

Configuration::Configuration(std::string const &filename)
	: _conf(filename)
{

}

Configuration::~Configuration()
{

}

void	Configuration::initialize()
{
	if (this->_conf.load())
	{
		Ultra::INISection	*section;
		if ((section = this->_conf.getSection("window")))
		{
			Configuration::X = section->getField<int>("x");
			Configuration::Y = section->getField<int>("y");
			Configuration::SCALE = section->getField<float>("scale");
			if (Configuration::SCALE < 0.5f)
				Configuration::SCALE = 0.5f;
			if (Configuration::SCALE > 1.0f)
				Configuration::SCALE = 1.0f;
			Configuration::MODE = section->getField<unsigned long>("mode");
			if (Configuration::MODE != 5 && Configuration::MODE != 8)
				Configuration::MODE = 5;
		}
		if ((section = this->_conf.getSection("sound")))
		{
			Configuration::GLOBAL_SOUND = section->getField<int>("global");
			if (Configuration::GLOBAL_SOUND < 0)
				Configuration::GLOBAL_SOUND = 0;
			if (Configuration::GLOBAL_SOUND > 100)
				Configuration::GLOBAL_SOUND = 100;
			Configuration::AMBIENT_SOUND = section->getField<int>("ambiance");
			if (Configuration::AMBIENT_SOUND < 0)
				Configuration::AMBIENT_SOUND = 0;
			if (Configuration::AMBIENT_SOUND > 100)
				Configuration::AMBIENT_SOUND = 100;
			Configuration::EFFECT_SOUND = section->getField<int>("effect");
			if (Configuration::EFFECT_SOUND < 0)
				Configuration::EFFECT_SOUND = 0;
			if (Configuration::EFFECT_SOUND > 100)
				Configuration::EFFECT_SOUND = 100;
		}
		if ((section = this->_conf.getSection("keyboard")))
		{
			Configuration::UP = section->getField<int>("up");
			Configuration::DOWN = section->getField<int>("down");
			Configuration::LEFT = section->getField<int>("left");
			Configuration::RIGHT = section->getField<int>("right");
			Configuration::SHOOT = section->getField<int>("shoot");
		}
	}
}
