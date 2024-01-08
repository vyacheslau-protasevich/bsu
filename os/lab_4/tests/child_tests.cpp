// tests/child_tests.cpp
#include "gtest/gtest.h"
#include "../Child.cpp"

TEST(ProcessChildMessageTest, MessageA) {
    EXPECT_EQ(processChildMessage(0, 5), 4);
}

TEST(ProcessChildMessageTest, MessageB) {
    EXPECT_EQ(processChildMessage(1, 5), 4);
}