#include "If.h"
#include "RpnStack.h"
#include "OperatorFactory.h"
#include "OperatorFactoryTestUtility.h"

#include <CppUTest/TestHarness.h>

TEST_GROUP(If) {
	OperatorFactory factory;
	If op;
	RpnStack values;

	CppUTestGroupIf() : op(factory.getOperatorNamed("+")) {
	}

	void setup() {
		values.push(5);
		values.push(9);
	}
};

TEST(If, IsRegistered) {
	validateFactoryRegistration("if", typeid(If));
}

TEST(If, WhenTrue) {
	values.push(1);
	op.invoke(values);

	LONGS_EQUAL(14, values.top());
}

TEST(If, WhenFalse) {
	values.push(0);
	op.invoke(values);

	LONGS_EQUAL(9, values.top());
}
