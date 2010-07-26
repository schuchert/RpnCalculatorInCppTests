#include "Sum.h"
#include "RpnStack.h"
#include "OperatorFactoryTestUtility.h"

#include <CppUTest/TestHarness.h>

TEST_GROUP(Sum) {
	RpnStack stack;
	Sum sum;
};

TEST(Sum, IsRegistered) {
	validateFactoryRegistration("sum", typeid(Sum));
}
TEST(Sum, StackLength1AfterSum) {
	sum.invoke(stack);
	LONGS_EQUAL(1, stack.size());
}

TEST(Sum, SumsSeveralValues) {
	stack.push(4);
	stack.push(1);
	stack.push(9);
	sum.invoke(stack);
	LONGS_EQUAL(14, stack.top());
}
