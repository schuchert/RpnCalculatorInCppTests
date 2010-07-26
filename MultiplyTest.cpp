#include "Multiply.h"
#include "OperatorFactoryTestUtility.h"

#include <memory>
#include <CppUTest/TestHarness.h>

TEST_GROUP(Multiply) {
};

TEST(Multiply, IsRegistered) {
	validateFactoryRegistration("*", typeid(Multiply));
}

TEST(Multiply, TwoNumbers) {
	std::shared_ptr<BinaryOperator> op(new Multiply);

	int result = op->doBinaryOperator(3, 4);
	LONGS_EQUAL(12, result);
}
