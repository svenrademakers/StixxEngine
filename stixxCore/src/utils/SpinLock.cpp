#include "utils/SpinLock.hpp"

namespace sx
{
	SpinLock::~SpinLock()
	{
		Unlock();
	}

	void SpinLock::Lock()
	{
		while (lock.test_and_set(std::memory_order_acquire))
			;
	}

	void SpinLock::Unlock()
	{
		lock.clear(std::memory_order_release);
	}
}