#include "PushConstant.h"
#include "RpnStack.h"


#include <CppUTest/TestHarness.h>

TEST_GROUP(PushConstant) {
	RpnStack values;
	PushConstant op;

	CppUTestGroupPushConstant() : op(42) {
	}
};

TEST(PushConstant, ValueOnTop) {
	op.invoke(values);

	LONGS_EQUAL(42, values.top());
}
