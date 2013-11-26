#ifndef  _POSITION2DCOMPONENT_H_
# define _POSITION2DCOMPONENT_H_

#include "APositionComponent.hpp"

class Position2DComponent : public Engine::APositionComponent<float, 2>
{
public:
	Position2DComponent();
	Position2DComponent(Position2DComponent const& cpy);
	~Position2DComponent();

	void	initialize();
	void	update();
	void	unload();

	float	getX() const;
	float	getY() const;

	void	setX(float x);
	void	setY(float y);

	Engine::AComponent*		clone() const;
	std::string const		getID() const;
};

#endif /* _POSITION2DCOMPONENT_H_ */
