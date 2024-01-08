#include <gtest/gtest.h>
#include "../child.cpp"

TEST(ProcessNumberTest, HandlesNegativeDivisibleBySix) {
    testing::internal::CaptureStdout();
    processNumber(-6);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "-6 ");
}

TEST(ProcessNumberTest, HandlesPositiveNumber) {
    testing::internal::CaptureStdout();
    processNumber(6);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "");
}

TEST(ProcessNumberTest, HandlesZero) {
    testing::internal::CaptureStdout();
    processNumber(0);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "");
}