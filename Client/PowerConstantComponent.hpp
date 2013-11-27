#ifndef  _ARMORCONSTANTCOMPONENT_H_
# define _ARMORCONSTANTCOMPONENT_H_

#include "APowerComponent.hpp"

class PowerConstantComponent : public Engine::APowerComponent
{
public:
	PowerConstantComponent(unsigned short power);
	PowerConstantComponent(PowerConstantComponent const& cpy);
	~PowerConstantComponent();

	void				initialize();
	void				update();
	void				unload();

	AComponent			*clone() const;
	std::string const	getID() const;
};


#endif 
