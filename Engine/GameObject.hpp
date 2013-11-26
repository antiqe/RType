#ifndef _GAMEOBJECT_H_
# include "AComponent.hpp"
# define _GAMEOBJECT_H_

# include <string>
# include <map>

# include "IObject.hpp"
# include "IPrototype.hpp"
# include "Container.hpp"

namespace Engine
{
	class GameObject : public IObject, public Ultra::IPrototype<GameObject>, protected Ultra::Container<AComponent>
	{
	private:
		std::string	_id;
	public:
		GameObject(std::string const& id);
		GameObject(GameObject const& cpy);
		~GameObject();
		GameObject&	operator=(GameObject const& cpy);

		std::string const&	getID() const;
		void				setID(std::string const& id);

		AComponent*	getComponent(std::string const& id) const;
		AComponent*	setComponent(AComponent* component);
		AComponent*	delComponent(std::string const& id);

		void			clearComponents();

		void			initialize();
		void			update();
		void			unload();
		GameObject*		clone() const;

		static std::string const	STARSHIP1;
		static std::string const	STARSHIP2;
		static std::string const	STARSHIP3;
		static std::string const	STARSHIP4;
	};
}

#endif
