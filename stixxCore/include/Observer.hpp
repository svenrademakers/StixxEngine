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
		Observer(const Observer&) = delete;
		Observer& operator=(const Observer&) = delete;
		virtual ~Observer();

	private:
		Subject<Observer>& subject;
	};

	template<typename T>
	class Subject
	{
	public:
		Subject() = default;
		Subject(const Subject&) = delete;
		Subject& operator=(const Subject&) = delete;
		virtual ~Subject();

		void Attach(Observer* observer);
		void Detach(Observer* observer);

		void NotifyObservers(const std::function<void(T&)>& call);

	private:
		std::unordered_set<Observer*> observers;
	};

	template<typename T>
	Subject<T>::~Subject()
	{ }

	template<typename T>
	void Subject<T>::Attach(Observer* observer)
	{
		observers.insert(observer);
	}
	
	template<typename T>
	void Subject<T>::Detach(Observer* observer)
	{
		if(observers.find(observer) != observers.end())
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