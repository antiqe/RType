#ifndef  _LIFECONSTANTCOMPONENT_H_
# define _LIFECONSTANTCOMPONENT_H_

#include "ALifeComponent.hpp"
#include "AArmorComponent.hpp"

class LifeConstantComponent : public Engine::ALifeComponent
{
private:
	Engine::AArmorComponent*	_armorComponent;
public:
	LifeConstantComponent(unsigned int max);
	LifeConstantComponent(unsigned int current, unsigned int max);
	LifeConstantComponent(LifeConstantComponent const& cpy);
	~LifeConstantComponent();

	void				initialize();
	void				update();
	void				unload();

	AComponent			*clone() const;
	std::string const	getID() const;
	void				takeDamage(unsigned int damage);
	void				heal(unsigned int heal);
};


#endif 
