#include "LogicTree.hpp"
#include "AComponent.hpp"
#include "ARenderComponent.hpp"
#include "APositionComponent.hpp"
#ifdef _WIN32
#include "WChrono.hpp"
#else
#include "LChrono.hpp"
#endif

namespace Engine
{
	LogicTree::LogicTree(Ultra::Factory<GameObject>* factory, short unity, size_t width, size_t height)
		: _unity(unity), _size(Ultra::Vector2D<size_t>(width, height)), _target(0), _factory(factory)
	{

	}

	LogicTree::~LogicTree()
	{
		if (this->_factory)
			delete this->_factory;
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
			APositionComponent<float, 2>*	component = dynamic_cast<APositionComponent<float, 2>*>(it->second->getComponent(AComponent::POSITION));
			if (component)
			{
				Ultra::Vector<float, 2>	vector = component->getPosition();
				if (vector.getCoordinate(Ultra::X) < 0.0f ||
					vector.getCoordinate(Ultra::X) > (float)(this->_size.getX() * this->_unity) ||
					vector.getCoordinate(Ultra::Y) < 0.0f ||
					vector.getCoordinate(Ultra::Y) > (float)(this->_size.getY() * this->_unity))
					list.push_back(it);
			}
			it->second->update();
		}
		for (std::list<std::map<std::string, GameObject*>::iterator>::iterator it = list.begin(); it != list.end(); ++it)
		{
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
			this->_pool[this->_load.front().second->getID()]->push(this->_load.front().second);
		}
		for (std::map<std::string, Ultra::Pool<GameObject>*>::iterator it = this->_pool.begin(); it != this->_pool.end(); ++it)
			delete it->second;
		this->_pool.clear();
		delete this->_chronoPool;
	}

	void	LogicTree::draw(IRender* render)
	{
		for (std::map<std::string, GameObject*>::iterator it; it != this->_objects.end(); ++it)
		{
			ARenderComponent* component = dynamic_cast<ARenderComponent*>(it->second->getComponent(AComponent::RENDER));
			if (component)
				component->draw(render);
		}
	}
}