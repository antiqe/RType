#ifndef  _ARMORCONSTANTCOMPONENT_H_
# define _ARMORCONSTANTCOMPONENT_H_

#include "AArmorComponent.hpp"

class ArmorConstantComponent : public Engine::AArmorComponent
{
public:
	ArmorConstantComponent(short armor, short min = -100, short max = 100);
	ArmorConstantComponent(ArmorConstantComponent const& cpy);
	~ArmorConstantComponent();

	void				initialize();
	void				update();
	void				unload();

	AComponent			*clone() const;
	std::string const	getID() const;
};


#endif 
