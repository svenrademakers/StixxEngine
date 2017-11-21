#ifndef SPINLOCK_HPP
#define SPINLOCK_HPP

#include <atomic>

namespace sx
{
	class SpinLock
	{
	public:
		SpinLock(bool setLock = false);
		SpinLock(const SpinLock&) = delete;
		SpinLock& operator=(const SpinLock&) = delete;
		virtual ~SpinLock();

		void Lock();
		void Unlock();

	private:
		std::atomic_flag lock;
	};
}

#endif
