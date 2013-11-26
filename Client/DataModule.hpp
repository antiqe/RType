#ifndef _DATAMODULE_H_
# define _DATAMODULE_H_

#include "ADataModule.hpp"
#include "Vector2D.hpp"
#include "Configuration.hpp"

class DataModule : public Engine::ADataModule
{
private:
	Configuration	_conf;
public:
	DataModule();
	~DataModule();

	void	initialize();
	void	update();
	void	unload();
};

#endif