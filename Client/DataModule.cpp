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
	this->_attr["globalSound"] = Ultra::Value(Configuration::GLOBAL_SOUND);
	this->_attr["ambientSound"] = Ultra::Value(Configuration::AMBIENT_SOUND);
	this->_attr["effectSound"] = Ultra::Value(Configuration::EFFECT_SOUND);
	this->_attr["upKey"] = Ultra::Value(Configuration::UP);
	this->_attr["downKey"] = Ultra::Value(Configuration::DOWN);
	this->_attr["leftKey"] = Ultra::Value(Configuration::LEFT);
	this->_attr["rightKey"] = Ultra::Value(Configuration::RIGHT);
	this->_attr["shootKey"] = Ultra::Value(Configuration::SHOOT);
	this->_attr["mapUnit"] = Ultra::Value((short)64);
	this->_attr["mapWidth"] = Ultra::Value((size_t)1600);
	this->_attr["mapHeight"] = Ultra::Value((size_t)900);
	this->_attr["login"] = Ultra::Value(std::string(""));
	this->_attr["id_room"] = Ultra::Value((unsigned short)0);
	this->_attr["id_player"] = Ultra::Value((char)0);
	this->_attr["id_ship"] = Ultra::Value((char)0);
	this->_attr["stateSpec"] = Ultra::Value((char)0);
	this->_attr["statePlayer"] = Ultra::Value((char)0);
	this->_attr["tmp"] = Ultra::Value(std::string(""));
}

void	DataModule::update()
{

}

void	DataModule::unload()
{

}