#include "RpnCalculator.h"
#include "OperatorFactory.h"

#include <CppUTest/TestHarness.h>

TEST_GROUP(ProgrammingTheCalculator){
	OperatorFactory *factory;
	RpnCalculator *calculator;

	void setup() {
		factory = new OperatorFactory;
		calculator = new RpnCalculator(*factory);
	}
	void teardown() {
		delete calculator;
		delete factory;
	}
};

TEST(ProgrammingTheCalculator, SingleStepProgram) {
	calculator->createProgramNamed("foo");
	calculator->addOperator("+");
	calculator->saveProgram();

	calculator->enterNumber(4);
	calculator->enterNumber(4);
	calculator->executeOperator("foo");

	LONGS_EQUAL(8, calculator->getX());
}
