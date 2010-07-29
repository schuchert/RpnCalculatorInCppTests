#include "RpnCalculator.h"

#include "OperatorFactory.h"

#include <CppUTest/TestHarness.h>

TEST_GROUP(RpnCalculator) {
	OperatorFactory *factory;
	RpnCalculator *calculator;

	void setup() {
		factory = new OperatorFactory();
		calculator = new RpnCalculator(*factory);
	}

	void teardown() {
		delete calculator;
		delete factory;
	}

};

TEST(RpnCalculator, AddWithNoParameters) {
	calculator->executeOperator("+");
	LONGS_EQUAL(0, calculator->getX());
}

TEST(RpnCalculator, Subtract) {
	calculator->enterNumber(42);
	calculator->enterNumber(17);
	calculator->executeOperator("-");

	LONGS_EQUAL(25, calculator->getX());
}

TEST(RpnCalculator, Add) {
	calculator->enterNumber(42);
	calculator->enterNumber(17);
	calculator->executeOperator("+");

	LONGS_EQUAL(59, calculator->getX());
}
