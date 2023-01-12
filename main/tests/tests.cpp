#include "tests.h"

TestParser::TestParser()
{
}

TestParser::~TestParser()
{
}

void TestParser::SetUp(void)
{
    inputData.setFilePath("../main/tests/test_file.csv");
}

TEST_F(TestParser, setFilePath_should_be_true)
{
    ASSERT_EQ(inputData.getFilePath(), "../main/tests/test_file.csv");
}

TEST_F(TestParser, parseFile_should_be_correct_when_file_exists)
{
    inputData.parseFile();
    ASSERT_EQ(inputData.getIdealThreshold(), 0.503922);
    ASSERT_THAT(inputData.getThresholds(), testing::ElementsAre(0.62549, 0.598039));
    ASSERT_THAT(inputData.getFMeasures(), testing::ElementsAre(0.001006, 0.00538, 0.001006));
}

TEST_F(TestParser, parseFile_should_fail_when_file_missing)
{
    inputData.setFilePath("../tests/test_file_missing.csv");
    inputData.parseFile();
    EXPECT_EQ(inputData.getThresholds().empty(), true);
    EXPECT_EQ(inputData.getFMeasures().empty(), true);
}

TestOperation::TestOperation()
{
}

TestOperation::~TestOperation()
{
}

TEST_F(TestOperation, correct_answer_geometric_mean)
{
    std::vector<double> array = {2.4, -53.7, 241.53, 23, -0.67};
    ASSERT_DOUBLE_EQ(operation.applyOperation(OperationType::GEOMETRIC_MEAN, array), 13.68333152994977);
}

TEST_F(TestOperation, correct_answer_arithmetic_mean)
{
    std::vector<double> array = {2.4, -53.7, 241.53, 23, -0.67};
    ASSERT_DOUBLE_EQ(operation.applyOperation(OperationType::ARITHMETIC_MEAN, array), 42.512);
}

TEST_F(TestOperation, correct_answer_multiplication)
{
    std::vector<double> array = {2.4, -53.7, 241.53, 23, -0.67};
    ASSERT_DOUBLE_EQ(operation.applyOperation(OperationType::MULTIPLICATION, array), 479688.43442400004);
}

TEST_F(TestOperation, correct_answer_min)
{
    std::vector<double> array = {2.4, -53.7, 241.53, 23, -0.67};
    ASSERT_DOUBLE_EQ(operation.applyOperation(OperationType::MIN, array), -53.7);
}

TEST_F(TestOperation, correct_answer_max)
{
    std::vector<double> array = {2.4, -53.7, 241.53, 23, -0.67};
    ASSERT_DOUBLE_EQ(operation.applyOperation(OperationType::MAX, array), 241.53);
}

TestRandomTree::TestRandomTree()
{
}

TestRandomTree::~TestRandomTree()
{
}

void TestRandomTree::SetUp(void)
{
    randomTree.getLeafSet().push_back(Node(0.5736));
    randomTree.getLeafSet().push_back(Node(0.243));
    randomTree.getLeafSet().push_back(Node(0.7641));
    randomTree.getLeafSet().push_back(Node(0.1858));
    randomTree.getLeafSet().push_back(Node(0.2474));
}

TEST_F(TestRandomTree, correct_random_tree_generation_links)
{
    std::queue<std::pair<int, OperationType>> choices;
    choices.push({3, OperationType::MULTIPLICATION});
    choices.push({2, OperationType::ARITHMETIC_MEAN});
    choices.push({2, OperationType::MULTIPLICATION});
    choices.push({2, OperationType::ARITHMETIC_MEAN});

    std::vector<int> leavesOrder;
    leavesOrder.push_back(4);
    leavesOrder.push_back(2);
    leavesOrder.push_back(3);
    leavesOrder.push_back(4);
    leavesOrder.push_back(1);
    leavesOrder.push_back(0);

    randomTree.generateTreeHierarchy(choices, leavesOrder);

    /*
    ordinea initiala a threshold-urilor: 0.2474, 0.7641, 0.1858, 0.2474, 0.243, 0.5736

            root
             /\
            /  \
           /    \
    firstChild  secondChild
        /\           /\
       /  \         /  \
      /    \       /    \
   0.2474  0.243 0.5736 nephew  
                         /|\
                        / | \
                       /  |  \
                      /   |   \
                0.2474 0.7641 0.1858
    */

    Node root = randomTree.getLeavesQueue().front();
    Node firstChild = root.getChildren()[0];
    Node secondChild = root.getChildren()[1];
    Node nephew = secondChild.getChildren()[1];

    ASSERT_DOUBLE_EQ(firstChild.getChildren()[0].getThreshold(), 0.2474);
    ASSERT_DOUBLE_EQ(firstChild.getChildren()[1].getThreshold(), 0.243);
    ASSERT_DOUBLE_EQ(nephew.getChildren()[0].getThreshold(), 0.2474);
    ASSERT_DOUBLE_EQ(nephew.getChildren()[1].getThreshold(), 0.7641);
    ASSERT_DOUBLE_EQ(nephew.getChildren()[2].getThreshold(), 0.1858);
    ASSERT_DOUBLE_EQ(secondChild.getChildren()[0].getThreshold(), 0.5736);
}

// TEST_F(TestRandomTree, correct_random_tree_root_calculation)
// {
//     randomTree.applyOp(&randomTree.getLeavesQueue().front());
//     ASSERT_DOUBLE_EQ(randomTree.getLeavesQueue().front().getValue(), 1); // 0.13267336920044959 sau 0.1326733692004496
// }

int run_tests(int argc, char **argv)
{
    // ::testing::InitGoogleTest(&argc, argv);
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}