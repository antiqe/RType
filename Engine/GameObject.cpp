#include <algorithm>
#include <functional>

#include "GameObject.hpp"

namespace Engine
{
	std::string const	GameObject::STARSHIP1 = "starship1";
	std::string const	GameObject::STARSHIP2 = "starship2";
	std::string const	GameObject::STARSHIP3 = "starship3";
	std::string const	GameObject::STARSHIP4 = "starship4";

	GameObject::GameObject(std::string const& id)
		: Ultra::Container<Engine::AComponent>(), _id(id)
	{

	}

	GameObject::GameObject(GameObject const& cpy)
		: Ultra::Container<Engine::AComponent>(), _id(cpy._id)
	{
		for (std::list<AComponent*>::const_iterator	it = cpy._contents.begin(); it != cpy._contents.end(); ++it)
			this->setComponent((*it)->clone());
	}

	GameObject::~GameObject()
	{
		this->clearContents();
	}

	GameObject&	GameObject::operator=(GameObject const& cpy)
	{
		Ultra::Container<AComponent>::operator=(cpy);
		if (this != &cpy)
		{
			for (std::list<AComponent*>::const_iterator	it = cpy._contents.begin(); it != cpy._contents.end(); ++it)
				this->setComponent((*it)->clone());
		}
		return (*this);
	}

	std::string const&	GameObject::getID() const
	{
		return (this->_id);
	}

	void			GameObject::setID(std::string const& id)
	{
		this->_id = id;
	}

	AComponent* GameObject::getComponent(std::string const& id) const
	{
		return (this->getContent(id));
	}

	AComponent* GameObject::setComponent(AComponent* component)
	{
		if (!component)
			return (0);
		AComponent*	old = Ultra::Container<AComponent>::setContent(component);
		if (old)
			old->_owner = 0;
		component->_owner = this;
		return (old);
	}

	AComponent*	GameObject::delComponent(std::string const& id)
	{
		return (this->delContent(id));
	}

	void	GameObject::clearComponents()
	{
		this->clearContents();
	}

	void	GameObject::initialize()
	{
		std::for_each(this->_contents.begin(), this->_contents.end(), std::mem_fun(&AComponent::initialize));
	}

	void	GameObject::update()
	{
		std::for_each(this->_contents.begin(), this->_contents.end(), std::mem_fun(&AComponent::update));
	}

	void	GameObject::unload()
	{
		std::for_each(this->_contents.begin(), this->_contents.end(), std::mem_fun(&AComponent::unload));
	}

	GameObject*	GameObject::clone() const
	{
		return (new GameObject(*this));
	}
}