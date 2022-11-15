#include <gtest/gtest.h>
#include "../main/parser/myfunctions.h"

TEST(myfunctions, add)
{
    ASSERT_EQ(add(10, 22), 32);
}

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}