#include "Nop.h"
#include "RpnStack.h"
#include "OperatorFactory.h"
#include "OperatorFactoryTestUtility.h"

#include <CppUTest/TestHarness.h>

TEST_GROUP(Nop) {
};

TEST(Nop, IsRegistered) {
	validateFactoryRegistration("nop", typeid(Nop));
}
