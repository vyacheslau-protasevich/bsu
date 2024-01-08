#include <gtest/gtest.h>
#include "../task_1.cpp"

// Тест для проверки корректности работы операций
TEST(OperationTest, Execute) {
    std::vector<double> numbers = {1.0, 2.0, 3.0, 4.0, 5.0};

    Addition addition;
    EXPECT_DOUBLE_EQ(addition.execute(numbers), 15.0);

    Multiplication multiplication;
    EXPECT_DOUBLE_EQ(multiplication.execute(numbers), 120.0);

    SumOfSquares sumOfSquares;
    EXPECT_DOUBLE_EQ(sumOfSquares.execute(numbers), 55.0);
}

// Тест для проверки корректности работы фабрики операций
TEST(OperationFactoryTest, Create) {
    Operation* operation;

    operation = OperationFactory::create(1);
    EXPECT_TRUE(dynamic_cast<Addition*>(operation) != nullptr);
    delete operation;

    operation = OperationFactory::create(2);
    EXPECT_TRUE(dynamic_cast<Multiplication*>(operation) != nullptr);
    delete operation;

    operation = OperationFactory::create(3);
    EXPECT_TRUE(dynamic_cast<SumOfSquares*>(operation) != nullptr);
    delete operation;

    EXPECT_THROW(OperationFactory::create(4), std::invalid_argument);
}

// Тест для проверки корректности работы обработчика файлов
TEST(FileProcessorTest, ProcessFiles) {
    // Здесь мы предполагаем, что в директории "test_files" есть файлы in_1.dat, in_2.dat и in_3.dat
    // с соответствующими операциями и числами
    FileProcessor fileProcessor("test_files", 2);
    fileProcessor.processFiles();

    // Проверяем, что в файле out.dat записана правильная сумма результатов
    std::ifstream inFile("out.dat");
    double totalSum;
    inFile >> totalSum;
    EXPECT_DOUBLE_EQ(totalSum, /* ожидаемая сумма результатов */);
}