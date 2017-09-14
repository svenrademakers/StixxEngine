#ifndef OBSERVER_HPP
#define OBSERVER_HPP

#include <unordered_set>
#include <functional>
#include <cassert>

namespace sx
{
	template<typename T>
	class Subject;

	class Observer
	{
	public:
		Observer(Subject<Observer>& subject);
		virtual ~Observer();
	};

	template<typename T>
	class Subject
	{
	public:
		void Attach(const Observer* observer);
		void Detach(const Observer* observer);

		void NotifyObservers(const std::function<void(T&)>& call);

	private:
		std::unordered_set<Observer*> observers;
	};

	template<typename T>
	void Subject<T>::Attach(const Observer* observer)
	{
		observers[observer];
	}
	
	template<typename T>
	void Subject<T>::Detach(const Observer* observer)
	{
		if(observers.find() != observers.end())
			observers.erase(observer);
	}

	template<typename T>
	void Subject<T>::NotifyObservers(const std::function<void(T&)>& call)
	{
		for (auto obs : observers)
		{
			assert(obs != nullptr);
			call(*obs);
		}
	}
}
#endif