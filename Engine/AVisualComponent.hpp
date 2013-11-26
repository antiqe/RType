#ifndef _AVISUALCOMPONENT_H_
# define _AVISUALCOMPONENT_H_

#include "AComponent.hpp"

namespace Engine
{
	class AVisualComponent : public AComponent
	{
	public:
		virtual ~AVisualComponent() {}

		std::string const	getFamilyID() const;
	};
}

#endif /* _AVISUALCOMPONENT_H_ */
