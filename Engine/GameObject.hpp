#ifndef _GAMEOBJECT_H_
# include "AComponent.hpp"
# define _GAMEOBJECT_H_

# include <string>
# include <map>

# include "IVisualObject.hpp"
# include "IPrototype.hpp"
# include "Container.hpp"

namespace Engine
{
	class GameObject : public IVisualObject, public Ultra::IPrototype<GameObject>, public Ultra::Container<AComponent>
	{
	private:
		std::string _familyID;
		std::string	_id;
	public:
		GameObject(std::string const& familyID, std::string const& id);
		GameObject(GameObject const& cpy);
		~GameObject();
		GameObject&	operator=(GameObject const& cpy);

		std::string const&	getID() const;
		std::string const&	getFamilyID() const;
		void				setID(std::string const& id);
		void				setFamilyID(std::string const& familyID);

		AComponent*	getComponent(std::string const& id) const;
		AComponent*	setComponent(AComponent* component);
		AComponent*	delComponent(std::string const& id);

		void			clearComponents();

		void			initialize();
		void			update();
		void			unload();
		void			draw(IRender* render);
		GameObject*		clone() const;

		static std::string const	PLAYER;
		static std::string const	BULLET;

		static std::string const	STARSHIP1;
		static std::string const	STARSHIP2;
		static std::string const	STARSHIP3;
		static std::string const	STARSHIP4;
	};
}

#endif
