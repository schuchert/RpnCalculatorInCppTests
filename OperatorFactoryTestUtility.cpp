#include "OperatorFactoryTestUtility.h"

#include "OperatorFactory.h"
#include "OperatorNotFoundException.h"
#include "Operator.h"
#include <typeinfo>

#include <CppUTest/TestHarness.h>

void validateFactoryRegistration(const std::string & opName, const std::type_info &expectedType) {
	try {
		OperatorFactory factory;
		spOp opSharedPtr = factory.getOperatorNamed(opName);
		const std::type_info &actualType = typeid(*opSharedPtr.get());
		CHECK(expectedType == actualType);
	} catch(OperatorNotFoundException &) {
		FAIL((opName + " is not registered").c_str());
	}
}
