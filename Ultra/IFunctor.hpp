#ifndef _IFUNCTOR_H_
# define _IFUNCTOR_H_

namespace Ultra
{
	template <typename T>
	class IFunctor
	{
	public:
		virtual ~IFunctor() {}

		virtual void	operator()(T const&) = 0;
	};
}

#endif /* _IFUNCTOR_H_ */
