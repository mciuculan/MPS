#include "test_parser.h"

TestParser::TestParser() {
    std::cout<<"Constructor";
}

TestParser::~TestParser() {

}

void TestParser::SetUp(void)
{
    parser.setFilePath("test_file.csv");
}

TEST_F(TestParser, setFilePath_should_be_true)
{
    ASSERT_EQ(parser.getFilePath(), "test_file.csv");
}

TEST_F(TestParser, parseFile_should_be_correct_when_file_exists)
{
    parser.parseFile();

    ASSERT_THAT(parser.getThresholds(), testing::ElementsAre(0.503922,0.625490,0.598039));
    ASSERT_THAT(parser.getFMeasures(), testing::ElementsAre(0.001006,0.001006,0.001006));
}

TEST_F(TestParser, parseFile_should_fail_when_file_missing)
{
    parser.setFilePath("test_file_missing.csv");
    parser.parseFile();
}

int main(int argc, char* argv[])
{
    // ::testing::InitGoogleTest(&argc, argv);
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}