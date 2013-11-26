#ifndef  _VECTOR2DCOMPONENT_H_
# define _VECTOR2DCOMPONENT_H_

#include "AVectorComponent.hpp"

class Vector2DComponent : public Engine::AVectorComponent<float, 2>
{
public:
	Vector2DComponent();
	Vector2DComponent(Vector2DComponent const& cpy);
	~Vector2DComponent();

	void				initialize();
	void				update();
	void				unload();

	AComponent			*clone() const;
	std::string const	getID() const;
};


#endif 
