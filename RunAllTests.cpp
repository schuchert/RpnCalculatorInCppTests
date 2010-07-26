#include <CppUTest/CommandLineTestRunner.h>

int main() {
	const char *args[] = { "", "-v" };
	return CommandLineTestRunner::RunAllTests(2, args);
}
