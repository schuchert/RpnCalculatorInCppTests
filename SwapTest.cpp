#include "Swap.h"
#include "RpnStack.h"
#include "OperatorFactoryTestUtility.h"
#include <CppUTest/TestHarness.h>

TEST_GROUP(Swap) {
};

TEST(Swap, IsRegistered) {
	validateFactoryRegistration("swap", typeid(Swap));
}

TEST(Swap,TwoNumbers) {
	RpnStack values;
	values.push(42);
	values.push(17);

	Swap swap;
	swap.invoke(values);

	LONGS_EQUAL(42, values.top());
	values.pop();
	LONGS_EQUAL(17, values.top());
}
