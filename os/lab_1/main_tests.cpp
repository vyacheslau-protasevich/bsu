#include <gtest/gtest.h>
using namespace testing;

#include "task.cpp"

TEST(FindNegativeNumbersBy6Test, ReturnsCorrectNumbers) {
    std::vector<int> input = {-6, -12, -18, -24, -30, 0, 6, 12, 18, 24, 30};
    std::vector<int> expected = {-6, -12, -18, -24, -30};
    ASSERT_EQ(findNegativeNumbersDivisibleBy6(&input), expected);
}

TEST(GenerateRandomNumberTest, ReturnsNumberInRange) {
    int number = generate_random_number();
    ASSERT_TRUE(number >= 0 && number <= 10);
}

TEST(GenerateRandomArrayTest, ReturnsArrayWithCorrectSize) {
    int size = 5;
    std::vector<int> array = generate_random_array(size);
    ASSERT_EQ(array.size(), size);
}