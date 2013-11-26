#ifndef _OBSERVER_H_
# define _OBSERVER_H_

#include <list>

namespace Ultra
{
	template <typename T> class ASubject;

	template <typename T>
	class AObserver
	{
	private:
		std::list<ASubject<T>*>	_subjects;

		typedef std::list<ASubject<T>*>::iterator		iterator;
		typedef std::list<ASubject<T>*>::const_iterator const_iterator;
	public:
		AObserver() {}

		virtual ~AObserver()
		{
			for (AObserver::iterator it = this->_subjects.begin(); it != this->_subjects.end(); ++it)
				(*it)->detach(this);
		}

		void	attach(ASubject<T>* subject, bool flag = true)
		{
			AObserver::const_iterator	it;

			it = std::find(this->_subjects.begin(), this->_subjects.end(), subject);
			if (it == this->_subjects.end())
			{
				this->_subjects.push_front(subject);
				if (flag)
					subject->attach(this, false);
			}
		}

		void	detach(ASubject<T>* subject, bool flag = true)
		{
			AObserver::iterator	it;

			it = std::find(this->_subjects.begin(), this->_subjects.end(), subject);
			if (it != this->_subjects.end())
			{
				this->_subjects.erase(it);
				if (flag)
					(*it)->detach(this, false);
			}
		}

		virtual void	update(ASubject<T>* subject) = 0;
	};
}

#include "ASubject.hpp"

#endif /* _OBSERVER_H_ */
