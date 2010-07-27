#include "WhitespaceTokenizer.h"

#include <CppUTest/TestHarness.h>

TEST_GROUP(WhitespaceTokenizer) {
	WhitespaceTokenizer tokenizer;
};

TEST(WhitespaceTokenizer, SingleTokenResultsInSingleTokenResult) {
	WhitespaceTokenizer::vector result = tokenizer.split("token");
	LONGS_EQUAL(1, result.size());
}

TEST(WhitespaceTokenizer, TwoTokenWithMultipleSpaces) {
	WhitespaceTokenizer::vector result = tokenizer.split("t1  t2");
	STRCMP_EQUAL("t1", result[0].c_str());
	STRCMP_EQUAL("t2", result[1].c_str());
}

TEST(WhitespaceTokenizer, LeadingWhitespaceIgnored) {
	WhitespaceTokenizer::vector result = tokenizer.split("t1  t2  ");
	STRCMP_EQUAL("t1", result[0].c_str());
	STRCMP_EQUAL("t2", result[1].c_str());
}

TEST(WhitespaceTokenizer, TrailingWhitespaceIgnored) {
	WhitespaceTokenizer::vector result = tokenizer.split("t1  t2  ");
	STRCMP_EQUAL("t1", result[0].c_str());
	STRCMP_EQUAL("t2", result[1].c_str());
}

TEST(WhitespaceTokenizer, WikispacesExamleParsesAsExpected) {
	WhitespaceTokenizer::vector result = tokenizer.split(
		": FLOOR5 ( n -- n' )   DUP 6 < IF DROP 5 ELSE 1 - THEN ;"
	);

	int index = 0;
	STRCMP_EQUAL(":", result[index++].c_str());
	STRCMP_EQUAL("FLOOR5", result[index++].c_str());
	STRCMP_EQUAL("(", result[index++].c_str());
	STRCMP_EQUAL("n", result[index++].c_str());
	STRCMP_EQUAL("--", result[index++].c_str());
	STRCMP_EQUAL("n'", result[index++].c_str());
	STRCMP_EQUAL(")", result[index++].c_str());
	STRCMP_EQUAL("DUP", result[index++].c_str());
	STRCMP_EQUAL("6", result[index++].c_str());
	STRCMP_EQUAL("<", result[index++].c_str());
	STRCMP_EQUAL("IF", result[index++].c_str());
	STRCMP_EQUAL("DROP", result[index++].c_str());
	STRCMP_EQUAL("5", result[index++].c_str());
	STRCMP_EQUAL("ELSE", result[index++].c_str());
	STRCMP_EQUAL("1", result[index++].c_str());
	STRCMP_EQUAL("-", result[index++].c_str());
	STRCMP_EQUAL("THEN", result[index++].c_str());
	STRCMP_EQUAL(";", result[index++].c_str());

}
