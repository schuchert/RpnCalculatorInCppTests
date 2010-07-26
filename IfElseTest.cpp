#include "IfElse.h"
#include "RpnStack.h"
#include "OperatorFactory.h"
#include "OperatorFactoryTestUtility.h"

#include <CppUTest/TestHarness.h>

TEST_GROUP(IfElse) {
	OperatorFactory factory;
	IfElse op;
	RpnStack values;

	CppUTestGroupIfElse() : op(getOp("+"), getOp("-")) {
	}

	spOp& getOp(const std::string &name) {
		return factory.getOperatorNamed(name);
	}

	void setup() {
		values.push(5);
		values.push(9);
	}
};

TEST(IfElse, IsRegistered) {
	validateFactoryRegistration("ifElse", typeid(IfElse));
}

TEST(IfElse, WhenTrue) {
	values.push(1);
	op.invoke(values);

	LONGS_EQUAL(14, values.top());
}

TEST(IfElse, WhenFalse) {
	values.push(0);
	op.invoke(values);

	LONGS_EQUAL(-4, values.top());
}
