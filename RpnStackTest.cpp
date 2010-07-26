#include "RpnStack.h"
#include <stack>

#include <CppUTest/TestHarness.h>

TEST_GROUP(RpnStack) {
	RpnStack stack;
};

TEST(RpnStack, PopOfEmptyStackLeavesSizeOf0) {
	stack.pop();
	LONGS_EQUAL(0, stack.size());
}

TEST(RpnStack, TopOfNewlyCreatedStackReturns0) {
	LONGS_EQUAL(0, stack.top());
}
