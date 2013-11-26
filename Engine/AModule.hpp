#ifndef _AMODULE_H_
# define _AMODULE_H_

#include <sys/types.h>
#include <string>

#include "IObject.hpp"
#include "ICompare.hpp"
#include "Governor.hpp"

namespace Engine
{
	class AModule : public IObject
	{
	public:	
		friend class Governor;
	protected:
		Governor*	_owner;
		size_t		_frame;
	public:
		class Compare : public Ultra::ICompare<AModule*>
		{
		private:
			std::string		_id;
		public:
			Compare(std::string const& id);
			~Compare() {}

			bool	operator()(AModule* const& module) const;
		};
		AModule(size_t frame = -1.0f);
		virtual ~AModule();

		virtual std::string	const&	getID() const = 0;

		bool	isImportant() const;
		
		size_t	getFrame() const;
		void	setFrame(size_t frame);

		static std::string const	EVENT;
		static std::string const	SOUND;
		static std::string const	RENDER;
		static std::string const	STATE;
		static std::string const	DATA;
		static std::string const	SOURCE;
		static std::string const	NETWORK;
		static std::string const	FACTORY;
	};
}

#endif
