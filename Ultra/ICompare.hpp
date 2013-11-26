#ifndef _ICOMPARE_H_
# define _ICOMPARE_H_

namespace Ultra
{
	template <typename T>
	class ICompare
	{
	public:
		virtual ~ICompare() {}

		virtual bool	operator()(T const&) const = 0;
	};
}

#endif /* _ICOMPARE_H_ */
