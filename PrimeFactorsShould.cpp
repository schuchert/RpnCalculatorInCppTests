#include "PrimeFactors.h"
#include "RpnStack.h"
#include "OperatorFactoryTestUtility.h"

#include <CppUTest/TestHarness.h>

TEST_GROUP(PrimeFactorsShould) {
	RpnStack stack;

	void given(int value) {
		stack.push(value);
	}

	void whenCalculatingPrimeFactors() {
		PrimeFactors op;
		op.invoke(stack);
	}

	void expect(int expected) {
		int actual = stack.top();
		stack.pop();
		LONGS_EQUAL(expected, actual);
	}

	void asWellAs(int expected) {
		expect(expected);
	}

	void andThenNoMoreResults() {
		LONGS_EQUAL(0, stack.size());
	}
};

TEST(PrimeFactorsShould, BeRegisteredInTheFactory) {
	validateFactoryRegistration("primeFactors", typeid(PrimeFactors));
}

TEST(PrimeFactorsShould, RemoveValueUnder2FromStack) {
	given(1);
	whenCalculatingPrimeFactors();
	expect(0);
	andThenNoMoreResults();
}

TEST(PrimeFactorsShould, Generate2ForAValueOf2) {
	given(2);
	whenCalculatingPrimeFactors();
	expect(2);
	andThenNoMoreResults();
}

TEST(PrimeFactorsShould, Generate3ForAValueOf3) {
	given(3);
	whenCalculatingPrimeFactors();
	expect(3);
	andThenNoMoreResults();
}

TEST(PrimeFactorsShould, Generate2And2ForAValueOf4) {
	given(4);
	whenCalculatingPrimeFactors();
	expect(2);
	asWellAs(2);
	andThenNoMoreResults();
}

TEST(PrimeFactorsShould, Generate5ForAValueOf5) {
	given(5);
	whenCalculatingPrimeFactors();
	expect(5);
	andThenNoMoreResults();
}

TEST(PrimeFactorsShould, Generate3And2ForAValueOf6) {
	given(6);
	whenCalculatingPrimeFactors();
	expect(3);
	asWellAs(2);
	andThenNoMoreResults();
}


TEST(PrimeFactorsShould, Generate2And2And2ForAValueOf8) {
	given(8);
	whenCalculatingPrimeFactors();
	expect(2);
	asWellAs(2);
	asWellAs(2);
	andThenNoMoreResults();
}

TEST(PrimeFactorsShould, Generate3And3ForAValueOf9) {
	given(9);
	whenCalculatingPrimeFactors();
	expect(3);
	asWellAs(3);
	andThenNoMoreResults();
}
