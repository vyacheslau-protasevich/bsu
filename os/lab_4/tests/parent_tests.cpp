// tests/parent_tests.cpp
#include "gtest/gtest.h"
#include "../Parent.cpp"

TEST(ProcessMessageTest, MessageC) {
    EXPECT_EQ(processMessage(0, 5), 4);
}

TEST(ProcessMessageTest, MessageD) {
    EXPECT_EQ(processMessage(1, 5), 4);
}