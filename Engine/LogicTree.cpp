#include "LogicTree.hpp"
#include "AComponent.hpp"
#include "ARenderComponent.hpp"
#include "APositionComponent.hpp"
#include "ASizeComponent.hpp"
#include "AVectorComponent.hpp"
#include "AShootComponent.hpp"
#include "IChrono.hpp"
#ifdef _WIN32
#include "WChrono.hpp"
#else
#include "LChrono.hpp"
#endif

namespace Engine
{
	LogicTree::LogicTree(Ultra::Factory<GameObject>* factory, short unity, size_t width, size_t height)
		: Widget("logicTree"), _unity(unity), _size(Ultra::Vector2D<size_t>(width, height)), _target(0), _factory(factory)
	{

	}

	LogicTree::~LogicTree()
	{

	}

	void	LogicTree::initialize()
	{

#ifdef _WIN32
		this->_chronoPool = new Ultra::Pool<Ultra::IChrono>(	Ultra::WChrono(), 25);
#else
		this->_chronoPool = new Ultra::Pool<Ultra::IChrono>(	Ultra::LChrono(), 25);
#endif
		if (this->_factory)
		{
			size_t	size;
			std::map<std::string, GameObject> objects = this->_factory->getAllObject();
			for (std::map<std::string, GameObject>::iterator it = objects.begin(); it != objects.end(); ++it)
			{
				if (it->second.getFamilyID() == GameObject::PLAYER)
					size = 4;
				else if (it->second.getFamilyID() == GameObject::BULLET)
					size = 50;
				else
					size = 10;
				this->_pool[it->second.getID()] = new Ultra::Pool<GameObject>(it->second, size);
			}
		}
	}

	void	LogicTree::update()
	{
		this->load();
		std::list<std::map<std::string, GameObject*>::iterator>	list;
		for (std::map<std::string, GameObject*>::iterator it = this->_objects.begin(); it != this->_objects.end(); ++it)
		{
			APositionComponent<float, 2>*	vectorComponent = dynamic_cast<APositionComponent<float, 2>*>(it->second->getComponent(AComponent::POSITION));
			if (vectorComponent)
			{
				ASizeComponent<2>*			sizeComponent = dynamic_cast<ASizeComponent<2>*>(it->second->getComponent(AComponent::SIZE));
				Ultra::Vector<size_t, 2>	size;
				if (sizeComponent)
					size = sizeComponent->getSize();
				Ultra::Vector<float, 2>		vector = vectorComponent->getPosition();
				if (vector.getCoordinate(Ultra::X) < 0.0f ||
					vector.getCoordinate(Ultra::X) + size.getCoordinate(Ultra::X) > (float)(this->_size.getX()) ||
					vector.getCoordinate(Ultra::Y) < 0.0f ||
					vector.getCoordinate(Ultra::Y) + size.getCoordinate(Ultra::Y) > (float)(this->_size.getY()))
					list.push_back(it);
			}
			it->second->update();
		}
		for (std::list<std::map<std::string, GameObject*>::iterator>::iterator it = list.begin(); it != list.end(); ++it)
		{
			if (this->_target == (*it)->second)
				this->_target = 0;
			this->_pool[(*it)->first]->push((*it)->second);
			this->_objects.erase(*it);
		}
	}

	void	LogicTree::load()
	{
		std::list<std::list<std::pair<Ultra::IChrono*, GameObject*> >::iterator>	list;
		for (std::list<std::pair<Ultra::IChrono*, GameObject*> >::iterator it = this->_load.begin(); it != this->_load.end(); ++it)
			if (it->first->isFinish())
				list.push_front(it);
		for (std::list<std::list<std::pair<Ultra::IChrono*, GameObject*> >::iterator>::iterator it = list.begin(); it != list.end(); ++it)
		{
			this->_chronoPool->push((*it)->first);
			(*it)->second->initialize();
			this->_objects[(*it)->second->getID()] = (*it)->second;
			this->_load.erase(*it);
		}
	}

	void	LogicTree::unload()
	{
		for (std::map<std::string, GameObject*>::iterator it = this->_objects.begin(); it != this->_objects.end(); ++it)
			this->_pool[it->second->getID()]->push(it->second);
		this->_objects.clear();
		while (!this->_load.empty())
		{
			this->_chronoPool->push(this->_load.front().first);
			this->_load.front().second->unload();
			this->_pool[this->_load.front().second->getID()]->push(this->_load.front().second);
		}
		for (std::map<std::string, Ultra::Pool<GameObject>*>::iterator it = this->_pool.begin(); it != this->_pool.end(); ++it)
			delete it->second;
		this->_pool.clear();
		delete this->_chronoPool;
	}

	void	LogicTree::draw(IRender* render)
	{
		for (std::map<std::string, GameObject*>::iterator it = this->_objects.begin(); it != this->_objects.end(); ++it)
			it->second->draw(render);
	}

	void	LogicTree::addObject(GameObject* object, float delay)
	{
		if (delay)
		{
			Ultra::IChrono*	chrono = this->_chronoPool->pop();
			chrono->launch(delay);
			this->_load.push_front(std::pair<Ultra::IChrono*, GameObject*>(chrono, object));
		}
		else
		{
			this->_objects[object->getID()] = object;
			object->initialize();
		}
	}

	void	LogicTree::setTarget(std::string const& id)
	{
		std::map<std::string, GameObject*>::iterator it = this->_objects.find(id);

		if (it != this->_objects.end())
			this->_target = it->second;
	}

	GameObject*	LogicTree::getTarget() const
	{
		return (this->_target);
	}

	void	LogicTree::move(Ultra::Vector2D<float> const& vector)
	{
		if (this->_target)
		{
			Engine::AVectorComponent<float, 2>*	vectorComponent = dynamic_cast<Engine::AVectorComponent<float, 2>*>(this->_target->getComponent(Engine::AComponent::VECTOR));
			if (vectorComponent)
			{
				Ultra::Vector<float, 2>	tmp;
				tmp.setCoordinate(vector.getX(), Ultra::X);
				tmp.setCoordinate(vector.getY(), Ultra::Y);
				vectorComponent->setVector(tmp);
			}
		}
	}

	void	LogicTree::preshoot()
	{
		if (this->_target)
		{
			Engine::AShootComponent*	shootComponent = dynamic_cast<Engine::AShootComponent*>(this->_target->getComponent(Engine::AComponent::SHOOT));
			if (shootComponent)
				shootComponent->active();
		}
	}

	void	LogicTree::shoot()
	{
		if (this->_target)
		{
			Engine::AShootComponent*	shootComponent = dynamic_cast<Engine::AShootComponent*>(this->_target->getComponent(Engine::AComponent::SHOOT));
			if (shootComponent)
				shootComponent->shoot();
		}
	}
}