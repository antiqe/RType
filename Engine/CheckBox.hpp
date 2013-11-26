#ifndef _CHECK_BOX_H_
# define _CHECK_BOX_H_

#include <string>

#include "Widget.hpp"
#include "IImage.hpp"
#include "Vector2D.hpp"
#include "IRender.hpp"
#include "AStateModule.hpp"
#include "ASourceModule.hpp"

namespace Engine
{
	class CheckBox : public Engine::Widget
	{
	public:
		enum Status
		{
			CHECKED_NORMAL = 0,
			CHECKED_CLICKED,
			CHECKED_HOVER,
			UNCHECKED_NORMAL,
			UNCHECKED_CLICKED,
			UNCHECKED_HOVER,
			STATUSSIZE
		};
	private:
		CheckBox::Status		_status;
		Engine::AStateModule*	_stateModule;
		ASourceModule*			_sourceModule;
		bool					_isChecked;
		Engine::IImage*			_img[CheckBox::STATUSSIZE];
		std::string				_file[CheckBox::STATUSSIZE];

	public:
		CheckBox(std::string const &name, std::string const &normalCheckedFile, std::string const &clickedCheckedFile,
			std::string const &hoverCheckedFile, std::string const &normalUncheckedFile,
			std::string const &clickedUncheckedFile, std::string const &hoverUncheckedFile, bool isChecked = false);
		virtual ~CheckBox();

		virtual	void	initialize();
		virtual void	update();
		virtual void	unload();
		virtual void	draw(Engine::IRender* render);

		void	toggle();

		void				setStatus(CheckBox::Status status);
		CheckBox::Status	getStatus() const;
		bool				isChecked() const;
	};
}

#endif
