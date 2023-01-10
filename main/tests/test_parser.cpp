#include "test_parser.h"

TestParser::TestParser()
{
}

TestParser::~TestParser()
{
}

void TestParser::SetUp(void)
{
    inputData.setFilePath("../tests/test_file.csv");
}

TEST_F(TestParser, setFilePath_should_be_true)
{
    ASSERT_EQ(inputData.getFilePath(), "../tests/test_file.csv");
}

TEST_F(TestParser, parseFile_should_be_correct_when_file_exists)
{

    // std::cout << "\n\nAICI " << parser.getFilePath() << "\n\n";

    inputData.parseFile();

    // std::cout << "\n\nAICI " << parser.getThresholds()[0] << "\n\n";

    ASSERT_THAT(inputData.getThresholds(), testing::ElementsAre(0.503922, 0.625490, 0.598039));
    ASSERT_THAT(inputData.getFMeasures(), testing::ElementsAre(0.001006, 0.001006, 0.001006));
}

TEST_F(TestParser, parseFile_should_fail_when_file_missing)
{
    inputData.setFilePath("../tests/test_file_missing.csv");
    inputData.parseFile();
}

int run_tests(int argc, char **argv)
{
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}

// int main(int argc, char* argv[])
// {
//     // ::testing::InitGoogleTest(&argc, argv);
//     ::testing::InitGoogleMock(&argc, argv);
//     return RUN_ALL_TESTS();
// }