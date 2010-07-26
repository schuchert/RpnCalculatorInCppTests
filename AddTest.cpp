#include "Add.h"
#include "RpnStack.h"
#include "OperatorFactoryTestUtility.h"
#include <CppUTest/TestHarness.h>

TEST_GROUP(Add) {
};

TEST(Add, IsRegistered) {
	validateFactoryRegistration("+", typeid(Add));
}

TEST(Add,TwoNumbers) {
	RpnStack values;
	values.push(42);
	values.push(17);

	Add add;
	add.invoke(values);

	LONGS_EQUAL(59, values.top());
}
