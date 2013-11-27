#ifndef _GAME_OBJECT_VIEWER_H_
# define _GAME_OBJECT_VIEWER_H_

#include <string>
#include <map>

#include "Widget.hpp"
#include "IImage.hpp"
#include "Vector2D.hpp"
#include "IRender.hpp"
#include "AStateModule.hpp"
#include "ASourceModule.hpp"
#include "Button.hpp"
#include "GameObject.hpp"
#include "ADataModule.hpp"

namespace Engine
{
	class GameObjectViewer : public Engine::Widget
	{
		ASourceModule*									_sourceModule;
		bool											_isChecked;
		std::map<std::string, GameObject*>				_content;
		std::map<std::string, GameObject*>::iterator	_focus;

		Button*	_prev;
		IImage*	_img;
		Button*	_next;

		ADataModule*	_dataModule;

	public:
		GameObjectViewer(std::string const &name, std::string const &normalNextFile, std::string const &clickedNextFile, 
			std::string const &hoverNextFile, std::string const &normalPrevFile, std::string const &clickedPrevFile, 
			std::string const &hoverPrevFile);
		virtual ~GameObjectViewer();

		virtual	void	initialize();
		virtual void	update();
		virtual void	unload();
		virtual void	draw(Engine::IRender* render);

		void	clear();
		void	push(std::string const &id, GameObject* gameObject);
		void	moveTo(std::string const &id);
		void	next();
		void	prev();

		std::string const&	getFocusId() const;
		GameObject const*	getFocusGameObject() const;
	};
}

#endif
