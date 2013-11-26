#ifndef _IPROTOTYPE_H_
# define _IPROTOTYPE_H_

namespace Ultra
{
	template <typename T>
	class IPrototype
	{
	public:
		virtual ~IPrototype() {}
		virtual T*	clone() const = 0;
	};
}

#endif /* _IPROTOTYPE_H_ */
