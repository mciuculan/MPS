#include "../parser/parser.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

class TestParser : public ::testing::Test
{
public:
	TestParser(void);
	virtual ~TestParser(void);
	virtual void SetUp(void);

public:
	Parser parser;
};

int run_tests(int argc, char **argv);