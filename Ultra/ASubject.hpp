#ifndef _ASUBJECT_H_
# define _ASUBJECT_H_

#include <list>

namespace Ultra
{
	template <typename T> class AObserver;

	template <typename T>
	class ASubject
	{
	private:
		T							_status;
		std::list<AObserver<T>*>	_observers;

		typedef std::list<AObserver<T>*>::iterator			iterator;
		typedef std::list<AObserver<T>*>::const_iterator	const_iterator;
	public:
		ASubject() {}

		virtual ~ASubject()
		{
			for (ASubject::iterator it = this->_observers.begin(); it != this->_observers.end(); ++it)
				(*it)->detach(this);
		}

		void	attach(AObserver<T>* observer, bool flag = true)
		{
			ASubject::const_iterator	it;

			it = std::find(this->_observers.begin(), this->_observers.end(), observer);
			if (it == this->_observers.end())
			{
				this->_observers.push_front(observer);
				if (flag)
					observer->attach(this, false);
			}
		}

		void	detach(AObserver<T>* observer, bool flag = true)
		{
			ASubject::iterator	it;

			it = std::find(this->_observers.begin(), this->_observers.end(), observer);
			if (it != this->_observers.end())
			{
				this->_observers.erase(it);
				if (flag)
					(*it)->detach(this, false);
			}
		}

		void	notify()
		{
			for (ASubject::iterator it = this->_observers.begin(); it != this->_observers.end(); ++it)
				(*it)->update(this);
		}

		virtual T	status() const = 0;
	};
}

#include "AObserver.hpp"

#endif /* _ASUBJECT_H_ */
