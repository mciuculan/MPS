#include "../inputData/inputData.h"
#include "../operation/operation.h"
#include "../randomTree/randomTree.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

class TestParser : public ::testing::Test
{
	public:
		InputData inputData;

		TestParser(void);
		virtual ~TestParser(void);
		virtual void SetUp(void);
};

class TestOperation : public ::testing::Test
{
	public:
		Operation operation;

		TestOperation(void);
		virtual ~TestOperation(void);
};

class TestRandomTree : public ::testing::Test
{
	public:
		RandomTree randomTree;

		TestRandomTree(void);
		virtual ~TestRandomTree(void);
        virtual void SetUp(void);
};

int run_tests(int argc, char **argv);