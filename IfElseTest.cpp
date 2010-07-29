#include "IfElse.h"
#include "RpnStack.h"
#include "OperatorFactory.h"
#include "OperatorFactoryTestUtility.h"

#include <CppUTest/TestHarness.h>

TEST_GROUP(IfElse) {
	OperatorFactory *factory;
	IfElse *op;
	RpnStack *values;

	void setup() {
		factory = new OperatorFactory;
		op = new IfElse(getOp("+"), getOp("-"));
		values = new RpnStack;

		values->push(5);
		values->push(9);
	}

	void teardown() {
		delete values;
		delete op;
		delete factory;
	}

	spOp& getOp(const std::string &name) {
		return factory->getOperatorNamed(name);
	}
};

TEST(IfElse, IsRegistered) {
	validateFactoryRegistration("ifElse", typeid(IfElse));
}

TEST(IfElse, WhenTrue) {
	values->push(1);
	op->invoke(*values);

	LONGS_EQUAL(14, values->top());
}

TEST(IfElse, WhenFalse) {
	values->push(0);
	op->invoke(*values);

	LONGS_EQUAL(-4, values->top());
}
