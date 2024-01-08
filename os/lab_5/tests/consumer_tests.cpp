#include <gtest/gtest.h>
#include "../Consume.cpp" // Include the file containing the function to test

TEST(PunctuationMarksTest, PositiveNos) {
    char testArray[] = {'a', 'b', '!', 'c', '?'};
    int length = sizeof(testArray)/sizeof(testArray[0]);
    std::vector<char> expectedOutput = {'!', '?'};
    ASSERT_EQ(expectedOutput, identifyPunctuationMarks(testArray, length));
}