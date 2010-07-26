#include "Dup.h"
#include "RpnStack.h"
#include "OperatorFactoryTestUtility.h"
#include <CppUTest/TestHarness.h>

TEST_GROUP(Dup) {
};

TEST(Dup, IsRegistered) {
	validateFactoryRegistration("dup", typeid(Dup));
}
TEST(Dup,TopOfStackDuplicated) {
	RpnStack values;
	values.push(42);

	Dup dup;
	dup.invoke(values);

	LONGS_EQUAL(2, values.size());
}
