#include <SFML/Graphics.hpp>

#include "DataModule.hpp"

DataModule::DataModule()
	: ADataModule("client.ini"), _conf("client.ini")
{

}

DataModule::~DataModule()
{

}

void	DataModule::initialize()
{
	this->_conf.initialize();
	this->_attr["winTitle"] = Ultra::Value(Configuration::NAME);
	this->_attr["winWidth"] = Ultra::Value((size_t)(Configuration::SCALE * 1600));
	this->_attr["winHeight"] = Ultra::Value((size_t)(Configuration::SCALE * 900));
	this->_attr["winMode"] = Ultra::Value((unsigned long)Configuration::MODE);
	this->_attr["winX"] = Ultra::Value(Configuration::X);
	this->_attr["winY"] = Ultra::Value(Configuration::Y);
}

void	DataModule::update()
{

}

void	DataModule::unload()
{

}