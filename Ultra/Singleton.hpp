#ifndef _SINGLETON_H_
# define _SINGLETON_H_

namespace Ultra
{
	template <typename T>
	class Singleton
	{
	protected:
		static T*	_instance;

		Singleton() {}
		~Singleton() {}
	public:
		static T*	getInstance()
		{
			if (Singleton::_instance == 0)
				Singleton::_instance = new T();
			return (Singleton::_instance);
		}

		static void	kill()
		{
			if (Singleton::_instance != 0)
			{
				delete Singleton::_instance;
				Singleton::_instance = 0;
			}
		}
	};

	template <typename T>
	T*	Singleton<T>::_instance = 0;
}

#endif /* _SINGLETON_H_ */
