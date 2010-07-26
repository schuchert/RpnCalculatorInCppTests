#include "CompositeOperator.h"

#include "OperatorFactory.h"
#include "RpnStack.h"

#include <CppUTest/TestHarness.h>

TEST_GROUP(CompositeOperator) {
	OperatorFactory factory;
	RpnStack stack;
};

TEST(CompositeOperator,ExecutesTwoContainedOperators) {
	CompositeOperator op;

	op.append(factory.getOperatorNamed("+"));
	op.append(factory.getOperatorNamed("-"));

	stack.push(4);
	stack.push(19);
	stack.push(-4);

	op.invoke(stack);

	LONGS_EQUAL(-11, stack.top());
}
