#include "OperatorFactory.h"
#include "RpnStack.h"
#include "CompositeOperator.h"
#include "PushConstant.h"
#include "IfElse.h"
#include <memory>
#include <CppUTest/TestHarness.h>

TEST_GROUP(MinProgram) {
	typedef std::shared_ptr<CompositeOperator> spCompositeOperator;

	OperatorFactory factory;
	RpnStack values;
	CompositeOperator *op;

	void setup() {
		op = new CompositeOperator;
		op->append(spOp(new PushConstant(2)));
		op->append(factory.getOperatorNamed("ndup"));
		op->append(factory.getOperatorNamed("<"));
		spCompositeOperator elsePart(new CompositeOperator());
		elsePart->append(factory.getOperatorNamed("swap"));
		elsePart->append(factory.getOperatorNamed("drop"));
		op->append(spOp(new IfElse(factory.getOperatorNamed("drop"), elsePart)));
	}

	void teardown() {
		delete op;
	}
};

TEST(MinProgram, FirstMin) {
	values.push(3);
	values.push(8);
	op->invoke(values);
	LONGS_EQUAL(3, values.top());
}

TEST(MinProgram, SecondMin) {
	values.push(9);
	values.push(-2);
	op->invoke(values);
	LONGS_EQUAL(-2, values.top());
}
