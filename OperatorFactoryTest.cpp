#include "OperatorFactory.h"
#include "OperatorFactoryTestUtility.h"

#include "Add.h"
#include "Subtract.h"
#include "Factorial.h"

#include "OperatorNotFoundException.h"
#include "OperatorNameAlreadyRegisteredException.h"

#include <CppUTest/TestHarness.h>

TEST_GROUP(OperatorFactory){
	OperatorFactory factory;
};

TEST(OperatorFactory,ThrowsExceptionForMissingOperatorName) {
	try {
		factory.getOperatorNamed("bogus missing operatior");
		FAIL("Should have thrown exception");
	} catch (OperatorNotFoundException &e) {
		// success
	}
}

TEST(OperatorFactory, ThrowsExceptionWhenAttemptingToReplaceExistingOperatorName) {
	spOp &anOp = factory.getOperatorNamed("+");
	try {
		factory.addOperator("+", anOp);
		FAIL("Should have thrown exception" );
	} catch (OperatorNameAlreadyRegisteredException &e) {
		// success
	}
}
