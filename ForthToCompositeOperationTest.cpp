#include "ForthToNamedOperatorBuilder.h"
#include "OperatorFactory.h"
#include "NamedOperator.h"
#include "RpnStack.h"

#include <CppUTest/TestHarness.h>

TEST_GROUP(Ftco) {
	RpnStack values;
	OperatorFactory factory;
	ForthToNamedOperatorBuilder builder;

	CppUTestGroupFtco() : builder(factory) {
	}
};

TEST(Ftco, SingleNamedCommandWellFormed) {
	values.push(3);
	NamedOperator op = builder.parse(": x drop ;");
	STRCMP_EQUAL("x", op.getName().c_str());
	op.invoke(values);

	LONGS_EQUAL(0, values.size());
}

TEST(Ftco, ThreeStepsCreatedAsSingleComposite) {
	values.push(7);
	values.push(3);
	NamedOperator op = builder.parse(": x dup * - ;");
	op.invoke(values);
	LONGS_EQUAL(-2, values.top());
}

TEST(Ftco, CanHandleConstantNumber) {
	NamedOperator op = builder.parse(": x 9 ;");
	op.invoke(values);
	LONGS_EQUAL(9, values.top());
}

TEST(Ftco, CanBuildCombinationOfConstantsAndExpressions) {
	NamedOperator op = builder.parse(": x 9 dup * ;");
	op.invoke(values);
	LONGS_EQUAL(81, values.top());
}
