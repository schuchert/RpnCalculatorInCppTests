#include "Subtract.h"
#include "RpnStack.h"

#include "OperatorFactoryTestUtility.h"

#include <CppUTest/TestHarness.h>

TEST_GROUP(Subtract) {
};

TEST(Subtract,SubtractRegistered) {
	validateFactoryRegistration("-", typeid(Subtract));
}

TEST(Subtract, TwoNumbers) {
	RpnStack values;
	values.push(42);
	values.push(17);

	Subtract subtract;
	subtract.invoke(values);

	LONGS_EQUAL(25, values.top());
}
