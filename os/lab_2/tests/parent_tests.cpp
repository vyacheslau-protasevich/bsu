#include <gtest/gtest.h>
#include "../parent.cpp"

TEST(StartChildTest, HandlesValidInput) {
    int arr[3] = {6, -6, 0};
    testing::internal::CaptureStdout();
    startChild(arr, 3);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "second not ok");
}
