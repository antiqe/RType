#include "GameObjectFactory.hpp"
#include "GameObject.hpp"

#include "Move2DComponent.hpp"
#include "Position2DComponent.hpp"
#include "SpeedConstantComponent.hpp"
#include "Vector2DComponent.hpp"
#include "LifeConstantComponent.hpp"
#include "ArmorConstantComponent.hpp"
#include "RenderAnimationComponent.hpp"
#include "RenderImageComponent.hpp"
#include "RenderStarshipComponent.hpp"
#include "Size2DComponent.hpp"

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
	object.setComponent(new RenderStarshipComponent(SFMLImage::STARSHIP1NORMAL, SFMLImage::STARSHIP1UP, SFMLImage::STARSHIP1DOWN));
	object.setComponent(new Size2DComponent(32, 13));
	this->learn(object.getID(), object);
	object.clearComponents();

	// Deuxième vaisseau
	object.setID(Engine::GameObject::STARSHIP2);
	object.setComponent(new Move2DComponent);
	object.setComponent(new SpeedConstantComponent(1.5f));
	object.setComponent(new Vector2DComponent);
	object.setComponent(new Position2DComponent);
	object.setComponent(new LifeConstantComponent(100));
	object.setComponent(new ArmorConstantComponent(0));
	object.setComponent(new RenderAnimationComponent(SFMLAnimation::STARSHIP2));
	object.setComponent(new Size2DComponent(32, 28));
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
	object.setComponent(new RenderAnimationComponent(SFMLAnimation::STARSHIP3));
	object.setComponent(new Size2DComponent(63, 48));
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
	object.setComponent(new RenderAnimationComponent(SFMLAnimation::STARSHIP4));
	object.setComponent(new Size2DComponent(49, 48));
	this->learn(object.getID(), object);
	object.clearComponents();
}

GameObjectFactory::~GameObjectFactory()
{

}