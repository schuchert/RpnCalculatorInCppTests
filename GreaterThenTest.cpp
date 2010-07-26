#include "GreaterThen.h"
#include "RpnStack.h"
#include "OperatorFactoryTestUtility.h"
#include <CppUTest/TestHarness.h>

TEST_GROUP(GreaterThen) {
};

TEST(GreaterThen, IsRegistered) {
	validateFactoryRegistration(">", typeid(GreaterThen));
}

TEST(GreaterThen, NotGreaterThen) {
	RpnStack values;
	values.push(17);
	values.push(42);

	GreaterThen greaterThen;
	greaterThen.invoke(values);

	LONGS_EQUAL(0, values.top());
}

TEST(GreaterThen, IsGreaterThen) {
	RpnStack values;
	values.push(42);
	values.push(17);

	GreaterThen greaterThen;
	greaterThen.invoke(values);

	LONGS_EQUAL(1, values.top());
}
