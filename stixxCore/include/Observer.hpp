#ifndef OBSERVER_HPP
#define OBSERVER_HPP

#include <unordered_set>
#include <functional>

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
		void Attach(Observer& observer);
		void NotifyObservers(const std::function<void(T&)>& call);

	private:
		//std::unordered_set<Observer&> observers;
	};

	template<typename T>
	void Subject<T>::Attach(Observer& observer)
	{
		//observers[observer];
	}

	template<typename T>
	void Subject<T>::NotifyObservers(const std::function<void(T&)>& call)
	{
		for (auto obs : observers)
			call(obs);
	}

}
#endif