#ifndef __SINGLETON_HPP__
#define __SINGLETON_HPP__

template <class T>
class Singleton
{
	protected:
		Singleton() {};
		// Dont forget to declare these two. You want to make sure they
		// are unaccessable otherwise you may accidently get copies of
		// your singelton appearing.
		Singleton(T const &);		// Don't Implement
		void operator=(T const &);	// Don't implement

	public:
		static T & GetInstance() {
			static T instance;	// Guaranteed to be destroyed.
			// Instantiated on first use.
			return instance;
		}
};

#endif
