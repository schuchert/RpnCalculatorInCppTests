#include "LessThen.h"
#include "RpnStack.h"
#include "OperatorFactoryTestUtility.h"
#include <CppUTest/TestHarness.h>

TEST_GROUP(LessThen) {
};

TEST(LessThen, IsRegistered) {
	validateFactoryRegistration("<", typeid(LessThen));
}

TEST(LessThen, NotLessThen) {
	RpnStack values;
	values.push(42);
	values.push(17);

	LessThen lessThen;
	lessThen.invoke(values);

	LONGS_EQUAL(0, values.top());
}

TEST(LessThen, IsLessThen) {
	RpnStack values;
	values.push(17);
	values.push(42);

	LessThen lessThen;
	lessThen.invoke(values);

	LONGS_EQUAL(1, values.top());
}
