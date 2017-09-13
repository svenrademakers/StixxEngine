#include "Observer.hpp"

namespace sx
{
	Observer::Observer(Subject<Observer>& subject)
	{
		subject.Attach(*this);
	}

	Observer::~Observer()
	{}
}
