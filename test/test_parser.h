#include "../main/parser/parser.h"
#include <gtest/gtest.h>

class TestParser : public ::testing::Test
{
public:
	TestParser(void);
	virtual ~TestParser(void);
	virtual void SetUp(void);


public:
	static Parser parser;
};