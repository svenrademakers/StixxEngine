#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "utils/Observer.hpp"

class TestObserver
	: public sx::Observer<TestObserver>
{
public:
	using sx::Observer<TestObserver>::Observer;

	virtual void Notify() = 0;
};

class TestObserver2
	: public sx::Observer<TestObserver2>
{
public:
	using sx::Observer<TestObserver2>::Observer;

	virtual void Notify2() = 0;
};

class TestSubject
	: public sx::Subject<TestObserver>
{};

class TestSubject2
	: public sx::Subject<TestObserver>
	, public sx::Subject<TestObserver2>
{
public:
	using sx::Subject<TestObserver>::NotifyObservers;
	using sx::Subject<TestObserver2>::NotifyObservers;

};

class ObserverMock
	: public TestObserver
{
public:
	ObserverMock(sx::Subject<TestObserver>& sub)
		: TestObserver(sub)
	{}

	MOCK_METHOD0(Notify, void());
};

class ObserverMock2
	: public TestObserver2
{
public:
	ObserverMock2(sx::Subject<TestObserver2>& sub)
		: TestObserver2(sub)
	{}

	MOCK_METHOD0(Notify2, void());
};

TEST(ObserverTest, notify_observers_one_to_many)
{
	TestSubject sub;
	ObserverMock observer1(sub);
	ObserverMock observer2(sub);

	EXPECT_CALL(observer1, Notify());
	EXPECT_CALL(observer2, Notify());

	sub.NotifyObservers([](TestObserver& observer) {
		observer.Notify();
	});
}

TEST(ObserverTest, notify_2_different_observer_types)
{
	TestSubject2 subject;
	ObserverMock observer1(subject);
	ObserverMock2 observer2(subject);

	EXPECT_CALL(observer2, Notify2());
	subject.NotifyObservers([](TestObserver2& observer) {
		observer.Notify2();
	});

	EXPECT_CALL(observer1, Notify());
	subject.NotifyObservers([](TestObserver& observer) {
		observer.Notify();
	});
}
