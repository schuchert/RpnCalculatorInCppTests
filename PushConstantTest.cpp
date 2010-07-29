#include "PushConstant.h"
#include "RpnStack.h"


#include <CppUTest/TestHarness.h>

TEST_GROUP(PushConstant) {
	RpnStack *values;
	PushConstant *op;

	void setup() {
		values = new RpnStack;
		op = new PushConstant(42);
	}

	void teardown() {
		delete op;
		delete values;
	}
};

TEST(PushConstant, ValueOnTop) {
	op->invoke(*values);

	LONGS_EQUAL(42, values->top());
}
