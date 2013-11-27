#ifndef  _SIZE2DCOMPONENT_H_
# define _SIZE2DCOMPONENT_H_

#include "ASizeComponent.hpp"
#include "AVectorComponent.hpp"
#include "ASpeedComponent.hpp"
#include "APositionComponent.hpp"

class Size2DComponent : public Engine::ASizeComponent<2>
{
public:
	Size2DComponent(size_t width, size_t height);
	Size2DComponent(Size2DComponent const& cpy);
	~Size2DComponent();

	void				initialize();
	void				update();
	void				unload();

	AComponent			*clone() const;
	std::string const	getID() const;
};


#endif 
