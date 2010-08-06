#include "ForthToNamedOperatorBuilder.h"
#include "OperatorFactory.h"
#include "NamedOperator.h"
#include "RpnStack.h"
#include "CompositeOperator.h"
#include "IfElse.h"
#include "PushConstant.h"
#include <iostream>
#include <typeinfo>

#include <CppUTest/TestHarness.h>

TEST_GROUP(Ftco) {
	RpnStack *values;
	OperatorFactory *factory;
	ForthToNamedOperatorBuilder *builder;

	void setup() {
		values = new RpnStack;
		factory = new OperatorFactory;
		builder = new ForthToNamedOperatorBuilder(*factory);
	}

	void teardown() {
		delete builder;
		delete factory;
		delete values;
	}
};

TEST(Ftco, SingleNamedCommandWellFormed) {
	values->push(3);
	NamedOperator op = builder->parse(": x drop ;");
	STRCMP_EQUAL("x", op.getName().c_str());
	op.invoke(*values);

	LONGS_EQUAL(0, values->size());
}

TEST(Ftco, ThreeStepsCreatedAsSingleComposite) {
	values->push(7);
	values->push(3);
	NamedOperator op = builder->parse(": x dup * - ;");
	op.invoke(*values);
	LONGS_EQUAL(-2, values->top());
}

TEST(Ftco, CanHandleConstantNumber) {
	NamedOperator op = builder->parse(": x 9 ;");
	op.invoke(*values);
	LONGS_EQUAL(9, values->top());
}

TEST(Ftco, CanBuildCombinationOfConstantsAndExpressions) {
	NamedOperator op = builder->parse(": x 9 dup * ;");
	op.invoke(*values);
	LONGS_EQUAL(81, values->top());
}

TEST(Ftco, CanBuildIf) {
	NamedOperator op = builder->parse(": x if drop then ;");
	values->push(17);
	values->push(7);
	values->push(1);
	op.invoke(*values);
	LONGS_EQUAL(17, values->top());
}

TEST(Ftco, CanBuildIfPartOfIfThen) {
	NamedOperator op = builder->parse(": x if drop 5 else 1 - then ;");
	values->push(7);
	values->push(3);
	values->push(1);
	op.invoke(*values);
	LONGS_EQUAL(5, values->top());
}

TEST(Ftco, CanBuildElsePartOfIfThen) {
	NamedOperator op = builder->parse(": x if drop 5 else 1 - then ;");
	values->push(7);
	values->push(3);
	values->push(0);
	op.invoke(*values);
	LONGS_EQUAL(2, values->top());
}

TEST(Ftco, CanExecuteEmptyThenOfIfThenElse) {
	NamedOperator op = builder->parse(": x if drop 5 else then ;");
	values->push(7);
	values->push(3);
	values->push(0);
	op.invoke(*values);
	LONGS_EQUAL(3, values->top());
}

TEST(Ftco, CanExecuteIfPartOfIfElseWithEmptyElse) {
	NamedOperator op = builder->parse(": x if drop 5 else then ;");
	values->push(7);
	values->push(3);
	values->push(1);
	op.invoke(*values);
	LONGS_EQUAL(5, values->top());
}

TEST(Ftco, CanBuildEmptyIfElseAndExecuteEmptyIf) {
	NamedOperator op = builder->parse(": x if else then ;");
	values->push(3);
	values->push(1);
	op.invoke(*values);
	LONGS_EQUAL(3, values->top());
}

TEST(Ftco, CanBuildEmptyIfElseAndExecuteEmptyElse) {
	NamedOperator op = builder->parse(": x if else then ;");
	values->push(3);
	values->push(0);
	op.invoke(*values);
	LONGS_EQUAL(3, values->top());
}

TEST(Ftco, CanImplementMinFunctionAndGetMinOnRight) {
	NamedOperator op = builder->parse(": min 2 ndup < if drop else swap drop then ;");
	values->push(9);
	values->push(3);
	op.invoke(*values);
	LONGS_EQUAL(3, values->top());
}

TEST(Ftco, CanImplementMinFunctionAndGetMinOnLeft) {
	NamedOperator op = builder->parse(": min 2 ndup < if drop else swap drop then ;");
	values->push(3);
	values->push(9);
	op.invoke(*values);
	LONGS_EQUAL(3, values->top());
}

using namespace std;

void spaces(int nesting);
void printIt(Operator *op, int nesting);
void printIt(CompositeOperator *op, int nesting);
void printJustList(CompositeOperator::const_iterator i, CompositeOperator::const_iterator end, int nesting);

void spaces(int nesting) {
	for(int i = 0; i < nesting; ++i)
		cout << "  ";
}

void printName(Operator *op, int nesting, const std::string &after = "") {
	spaces(nesting);
	cout << typeid(*op).name() << after << endl;
}

void printIt(CompositeOperator *op, int nesting) {
	printName(static_cast<Operator*>(op), nesting);
	printJustList(op->begin(), op->end(), nesting);
}

void printJustList(CompositeOperator::const_iterator i, CompositeOperator::const_iterator end, int nesting) {
	for(;i != end; ++i) {
		Operator *current = (*i).get();
		if(dynamic_cast<IfElse*>(current)) {
			IfElse *ifElse = static_cast<IfElse*>(current);
			printIt(ifElse, nesting + 1);
			spaces(nesting + 1);
			cout << "else" << endl;
			CompositeOperator &elseBlock = ifElse->getElseBlock();
			printJustList(elseBlock.begin(), elseBlock.end(), nesting + 1);
		} else if(dynamic_cast<CompositeOperator*>(current))
			printIt(static_cast<CompositeOperator*>(current), nesting + 1);
		else {
			PushConstant *pc = dynamic_cast<PushConstant*>(current);
			std::string count = "";
			if(pc != 0) {
				char value[10];
				snprintf(value, 10, "(%d)", pc->getValue());
				count += value;
			}
			printName(current, nesting + 1, count);
		}
	}
}

void printIt(NamedOperator &namedOp) {
	CompositeOperator *op = dynamic_cast<CompositeOperator*>(namedOp.getOp().get());
	cout << endl << "------------------------------------------";
	printJustList(op->begin(), op->end(), 0);
	cout << "------------------------------------------" << endl;
}

TEST(Ftco, NestedIfElseTrueTrue) {
	NamedOperator op = builder->parse( ": x < if < if 1 else 2 then else < if 3 else 4 then then ;" );
	values->push(4);
	values->push(5);
	values->push(4);
	values->push(5);
	op.invoke(*values);
	LONGS_EQUAL(1, values->top());
}

TEST(Ftco, NestedIfElseTrueFalse) {
	NamedOperator op = builder->parse( ": x < if < if 1 else 2 then else < if 3 else 4 then then ;" );
	values->push(5);
	values->push(4);
	values->push(4);
	values->push(5);
	op.invoke(*values);
	LONGS_EQUAL(2, values->top());
}

TEST(Ftco, NestedIfElseFalseTrue) {
	NamedOperator op = builder->parse( ": x < if < if 1 else 2 then else < if 3 else 4 then then ;" );
	values->push(4);
	values->push(5);
	values->push(5);
	values->push(4);
	op.invoke(*values);
	LONGS_EQUAL(3, values->top());
}

TEST(Ftco, NestedIfElseFalseFalse) {
	NamedOperator op = builder->parse( ": x < if < if 1 else 2 then else < if 3 else 4 then then ;" );
	values->push(5);
	values->push(4);
	values->push(5);
	values->push(4);
	op.invoke(*values);
	LONGS_EQUAL(4, values->top());
}

static NamedOperator buildBigOne(ForthToNamedOperatorBuilder *builder) {
	return builder->parse(": x 2 ndup < if drop dup 10 > if 2 * else 1 - then else swap drop dup -10 < if 2 * else 13 + then then ;");
}

TEST(Ftco, BigNestedIfPathTrueTure) {
	NamedOperator op = buildBigOne(builder);
	values->push(30);
	values->push(50);
	op.invoke(*values);
	LONGS_EQUAL(60, values->top());
}

TEST(Ftco, BigNestedIfTrueFalse) {
	NamedOperator op = buildBigOne(builder);
	values->push(3);
	values->push(50);
	op.invoke(*values);
	LONGS_EQUAL(2, values->top());
}

TEST(Ftco, BigNestedIfFalseTrue) {
	NamedOperator op = buildBigOne(builder);
	values->push(10);
	values->push(-20);
	op.invoke(*values);
	LONGS_EQUAL(-40, values->top());
}

TEST(Ftco, BigNestedIfFalseFalse) {
	NamedOperator op = buildBigOne(builder);
	values->push(10);
	values->push(-1);
	op.invoke(*values);
	LONGS_EQUAL(12, values->top());
}
