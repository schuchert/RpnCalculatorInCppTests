#include "IfElse.h"
#include "If.h"
#include "RpnStack.h"
#include "OperatorFactory.h"

#include <CppUTest/TestHarness.h>

TEST_GROUP(IfElseBuilding) {
	OperatorFactory factory;
	RpnStack values;

	spOp& getOp(const std::string &name) {
		return factory.getOperatorNamed(name);
	}
};

TEST(IfElseBuilding, CanBuildWithIfAsFirstParameter) {
	spOp ifOp(new If(getOp("drop")));
	IfElse ifElseOp(ifOp, getOp("swap"));

	values.push(4);
	values.push(9);
	values.push(1);

	ifElseOp.invoke(values);

	LONGS_EQUAL(4, values.top());
}
