#ifndef _LOGICTREE_H_
# define _LOGICTREE_H_

#include <map>
#include <string>
#include <list>
#include <functional>

#include "Factory.hpp"
#include "Pool.hpp"
#include "IVisualObject.hpp"
#include "GameObject.hpp"
#include "Vector2D.hpp"
#include "IChrono.hpp"
#include "IRender.hpp"
#include "Widget.hpp"

namespace Engine
{
	class LogicTree : public Widget
	{
	private:	
		short												_unity;
		Ultra::Vector2D<size_t>								_size;
		GameObject*											_target;
		Ultra::Factory<GameObject>*							_factory;
		Ultra::Pool<Ultra::IChrono>*						_chronoPool;
		std::map<std::string, Ultra::Pool<GameObject>* >	_pool;	
		std::map<std::string, GameObject*>					_objects;
		std::list<std::pair<Ultra::IChrono*, GameObject*> >	_load;

		void	load();
	public:
		LogicTree(Ultra::Factory<GameObject>* factory, short unity = 64, size_t width = 32, size_t height = 16);
		~LogicTree();

		void	initialize();
		void	update();
		void	unload();
		void	draw(IRender* render);

		// to delete
		void	addObject(GameObject* object);
	};
}

#endif