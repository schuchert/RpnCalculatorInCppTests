#include "Divide.h"
#include "RpnStack.h"
#include "OperatorFactoryTestUtility.h"
#include <CppUTest/TestHarness.h>

TEST_GROUP(Divide) {
};

TEST(Divide, IsRegistered) {
	validateFactoryRegistration("/", typeid(Divide));
}
TEST(Divide,TwoNumbers) {
	RpnStack values;
	values.push(6*7);
	values.push(7);

	Divide divide;
	divide.invoke(values);

	LONGS_EQUAL(6, values.top());
}
