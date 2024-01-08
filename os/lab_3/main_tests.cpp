#include <gtest/gtest.h>
using namespace testing;

#include "main.cpp"

TEST(GenerateArrayTest, ArraySize) {
    std::vector<int> array = generateArray(10);
    EXPECT_EQ(array.size(), 10);
}
