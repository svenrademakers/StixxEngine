#ifndef OBSERVER_HPP
#define OBSERVER_HPP

#include <unordered_set>
#include <functional>
#include <cassert>

namespace sx
{
	template<typename T>
	class Subject;

	template<typename T>
	class Observer
	{
	public:
		Observer(Subject<T>& subject)
			: subject(subject)
		{
			subject.Attach(this);
		}

		~Observer()
		{
			subject.Detach(this);
		}		
		
		Observer(const Observer&) = delete;
		Observer& operator=(const Observer&) = delete;

	private:
		Subject<T>& subject;
	};

	template<typename T>
	class Subject
	{
	public:
		typedef Observer<T> ObserverType;

		Subject() = default;
		Subject(const Subject&) = delete;
		Subject& operator=(const Subject&) = delete;
		virtual ~Subject();

		void Attach(ObserverType* observer);
		void Detach(ObserverType* observer);

		void NotifyObservers(const std::function<void(T&)>& call);

	private:
		std::unordered_set<ObserverType*> observers;
	};

	template<typename T>
	Subject<T>::~Subject()
	{ }

	template<typename T>
	void Subject<T>::Attach(ObserverType* observer)
	{
		observers.insert(observer);
	}
	
	template<typename T>
	void Subject<T>::Detach(ObserverType* observer)
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
			call(*static_cast<T*>(obs));
		}
	}
}
#endif