#include "Configuration.hpp"

int					Configuration::X = 0;
int					Configuration::Y = 0;
float				Configuration::SCALE = 0.8f;
unsigned long		Configuration::MODE  = 5;
std::string const	Configuration::NAME = "RTYPE";

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
			if (Configuration::SCALE < 0.1f)
				Configuration::SCALE = 0.8f;
			Configuration::MODE = section->getField<unsigned long>("mode");
			if (Configuration::MODE != 5 && Configuration::MODE != 8)
				Configuration::MODE = 5;
		}
	}
}
