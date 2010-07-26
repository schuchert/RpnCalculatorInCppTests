#include "Factorial.h"
#include "RpnStack.h"
#include "OperatorFactoryTestUtility.h"

#include <CppUTest/TestHarness.h>

TEST_GROUP(Factorial) {
	RpnStack stack;
	Factorial factorial;
};

TEST(Factorial, IsRegistered) {
	validateFactoryRegistration("!", typeid(Factorial));
}

TEST(Factorial, Of5Is120) {
	stack.push(5);
	factorial.invoke(stack);
	LONGS_EQUAL(120, stack.top());
}

TEST(Factorial, Of0Is1) {
	factorial.invoke(stack);
	LONGS_EQUAL(1, stack.top());
}

TEST(Factorial, OfNegative1Is1) {
	stack.push(-1);
	factorial.invoke(stack);
	LONGS_EQUAL(1, stack.top());
}

TEST(Factorial, LeavesRestOfStackAlone) {
	stack.push(-1);
	stack.push(4);
	factorial.invoke(stack);
	LONGS_EQUAL(2, stack.size());
}
