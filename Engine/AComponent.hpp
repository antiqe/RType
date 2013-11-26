#ifndef _ACOMPONENT_H_
# define _ACOMPONENT_H_

#include <string>

#include "IObject.hpp"
#include "IPrototype.hpp"
#include "ICompare.hpp"

namespace Engine
{
	class GameObject;

	class AComponent : public IObject, public Ultra::IPrototype<AComponent>
	{
	public:
		friend class GameObject;
	private:
		GameObject*	_owner;

	public:
		class Compare : public Ultra::ICompare<AComponent*>
		{
		private:	
			std::string _id;
		public:
			Compare(std::string const& id);
			~Compare();

			bool	operator()(AComponent* const& component) const;
		};

		AComponent();
		AComponent(AComponent const& cpy);
		virtual ~AComponent();

		GameObject*	getOwner() const;

		virtual std::string const	getID() const = 0;
		virtual std::string const	getFamilyID() const = 0;

		static std::string const	RENDER;
		static std::string const	POSITION;
		static std::string const	ROTATION;
		static std::string const	MOVE;
		static std::string const	VECTOR;
		static std::string const	SPEED;
		static std::string const	LIFE;
		static std::string const	COLLIDOR;
		static std::string const	SIZE;
		static std::string const	SHOOT;
		static std::string const	ARMOR;
		static std::string const	EXPLODE;
		static std::string const	SHIELD;
		static std::string const	INVINCIBILITY;
		static std::string const	NETWORK;
		static std::string const	SCORE;
		static std::string const	LEVEL;
		static std::string const	SOUND;
	};
}

#ifdef _GAMEOBJECT_H_
#include "GameObject.hpp"
#endif

#endif /* _ACOMPONENT_H_ */