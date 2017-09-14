#include "Observer.hpp"

namespace sx
{
	Observer::Observer(Subject<Observer>& subject)
		: subject(subject)
	{
		subject.Attach(this);
	}

	Observer::~Observer()
	{
		subject.Detach(this);
	}
}
