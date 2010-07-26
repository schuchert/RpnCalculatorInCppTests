#include "NDup.h"
#include "RpnStack.h"
#include "OperatorFactoryTestUtility.h"
#include <CppUTest/TestHarness.h>

TEST_GROUP(NDup) {
	RpnStack values;
	NDup ndup;

	void validateTopOfStackIs(int expected) {
		LONGS_EQUAL(expected, values.top());
		values.pop();
	}
};

TEST(NDup, IsRegistered) {
	validateFactoryRegistration("ndup", typeid(NDup));

}

TEST(NDup,TopOfStackDuplicated) {
	values.push(42);
	values.push(1);

	ndup.invoke(values);

	LONGS_EQUAL(2, values.size());
}

TEST(NDup, Dup3ForStackOfSize3ResultsInStackOfSize6) {
	for(int i = 10; i <= 30; i += 10)
		values.push(i);

	values.push(3);

	ndup.invoke(values);

	LONGS_EQUAL(6, values.size());
}

TEST(NDup, DupTop2ItemsInSize3StackHandledCorrectly) {
	values.push(4);
	values.push(8);
	values.push(-3);
	values.push(2);

	ndup.invoke(values);

	validateTopOfStackIs(-3);
	validateTopOfStackIs(8);
	validateTopOfStackIs(-3);
	validateTopOfStackIs(8);
	validateTopOfStackIs(4);
	validateTopOfStackIs(0);
}
