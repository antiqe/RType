#include "GameObjectFactory.hpp"
#include "GameObject.hpp"

#include "Move2DComponent.hpp"
#include "Position2DComponent.hpp"
#include "SpeedConstantComponent.hpp"
#include "Vector2DComponent.hpp"
#include "LifeConstantComponent.hpp"
#include "ArmorConstantComponent.hpp"

GameObjectFactory::GameObjectFactory()
{
	Engine::GameObject	object("", "");

	// Player
	object.setFamilyID(Engine::GameObject::PLAYER);
	// Premier vaisseau
	object.setID(Engine::GameObject::STARSHIP1);
	object.setComponent(new Move2DComponent);
	object.setComponent(new SpeedConstantComponent(1.5f));
	object.setComponent(new Vector2DComponent);
	object.setComponent(new Position2DComponent);
	object.setComponent(new LifeConstantComponent(100));
	object.setComponent(new ArmorConstantComponent(25));
	this->learn(object.getID(), object);
	object.clearComponents();

	// Deuxième vaisseau
	object.setID(Engine::GameObject::STARSHIP2);
	object.setComponent(new Move2DComponent);
	object.setComponent(new SpeedConstantComponent(2.0f));
	object.setComponent(new Vector2DComponent);
	object.setComponent(new Position2DComponent);
	object.setComponent(new LifeConstantComponent(100));
	object.setComponent(new ArmorConstantComponent(-25));
	this->learn(object.getID(), object);
	object.clearComponents();

	// Troisième vaisseau
	object.setID(Engine::GameObject::STARSHIP3);
	object.setComponent(new Move2DComponent);
	object.setComponent(new SpeedConstantComponent(1.8f));
	object.setComponent(new Vector2DComponent);
	object.setComponent(new Position2DComponent);
	object.setComponent(new LifeConstantComponent(100));
	object.setComponent(new ArmorConstantComponent(0));
	this->learn(object.getID(), object);
	object.clearComponents();

	// Quatrième vaisseau
	object.setID(Engine::GameObject::STARSHIP4);
	object.setComponent(new Move2DComponent);
	object.setComponent(new SpeedConstantComponent(1.0f));
	object.setComponent(new Vector2DComponent);
	object.setComponent(new Position2DComponent);
	object.setComponent(new LifeConstantComponent(100));
	object.setComponent(new ArmorConstantComponent(50));
	this->learn(object.getID(), object);
	object.clearComponents();
}

GameObjectFactory::~GameObjectFactory()
{

}