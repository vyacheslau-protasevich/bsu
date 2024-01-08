#include <gtest/gtest.h>
#include <fstream>
#include <sstream>

#include "../task_2.cpp"

TEST(MatrixTest, MultiplyMatrices) {
    Matrix A(2, 3);
    A[0][0] = 1; A[0][1] = 2; A[0][2] = 3;
    A[1][0] = 4; A[1][1] = 5; A[1][2] = 6;

    Matrix B(3, 2);
    B[0][0] = 7; B[0][1] = 8;
    B[1][0] = 9; B[1][1] = 10;
    B[2][0] = 11; B[2][1] = 12;

    Matrix C = multiplyMatrices(A, B, 2);

    EXPECT_EQ(C[0][0], 58);
    EXPECT_EQ(C[0][1], 64);
    EXPECT_EQ(C[1][0], 139);
    EXPECT_EQ(C[1][1], 154);
}

TEST(MatrixTest, WriteToFile) {
    Matrix C(2, 2);
    C[0][0] = 58; C[0][1] = 64;
    C[1][0] = 139; C[1][1] = 154;

    std::string filename = "test.txt";
    writeToFile(C, filename);

    std::ifstream file(filename);
    std::stringstream buffer;
    buffer << file.rdbuf();

    std::string expected = "58 64 \n139 154 \n";
    EXPECT_EQ(buffer.str(), expected);
}