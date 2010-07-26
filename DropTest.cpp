#include "Drop.h"
#include "RpnStack.h"
#include "OperatorFactoryTestUtility.h"
#include <CppUTest/TestHarness.h>

TEST_GROUP(Drop) {
};

TEST(Drop, IsRegistered) {
	validateFactoryRegistration("drop", typeid(Drop));
}
TEST(Drop,TwoNumbers) {
	RpnStack values;
	values.push(42);
	values.push(17);

	Drop drop;
	drop.invoke(values);

	LONGS_EQUAL(42, values.top());
}
