#include <vector>
#include <numeric>
#include <cmath>
#include <thread>
#include <fstream>
#include <sstream>
#include <iostream>
#include <filesystem>
#include <mutex>

// Абстрактный класс операции
class Operation {
public:
    virtual double execute(const std::vector<double>& numbers) = 0;
};

// Классы конкретных операций
class Addition : public Operation {
public:
    double execute(const std::vector<double>& numbers) override {
        return std::accumulate(numbers.begin(), numbers.end(), 0.0);
    }
};

class Multiplication : public Operation {
public:
    double execute(const std::vector<double>& numbers) override {
        return std::accumulate(numbers.begin(), numbers.end(), 1.0, std::multiplies<double>());
    }
};

class SumOfSquares : public Operation {
public:
    double execute(const std::vector<double>& numbers) override {
        return std::accumulate(numbers.begin(), numbers.end(), 0.0, [](double a, double b) { return a + b * b; });
    }
};

// Фабрика операций
class OperationFactory {
public:
    static Operation* create(int operationType) {
        switch (operationType) {
        case 1:
            return new Addition();
        case 2:
            return new Multiplication();
        case 3:
            return new SumOfSquares();
        default:
            throw std::invalid_argument("Invalid operation type");
        }
    }
};

// Класс обработчика файлов
class FileProcessor {
public:
    FileProcessor(const std::string& directory, int threadCount) : directory(directory), threadCount(threadCount) {}

    void processFiles() {
        std::vector<std::thread> threads;
        for (const auto& entry : std::filesystem::directory_iterator(directory)) {
            threads.push_back(std::thread(&FileProcessor::processFile, this, entry.path()));
            if (threads.size() == threadCount) {
                for (auto& thread : threads) {
                    thread.join();
                }
                threads.clear();
            }
        }
        for (auto& thread : threads) {
            thread.join();
        }
        std::ofstream outFile("out.dat");
        outFile << totalSum;
    }

private:
    void processFile(const std::filesystem::path& filePath) {
        std::ifstream inFile(filePath);
        int operationType;
        inFile >> operationType;
        std::vector<double> numbers;
        double number;
        while (inFile >> number) {
            numbers.push_back(number);
        }
        Operation* operation = OperationFactory::create(operationType);
        double result = operation->execute(numbers);
        delete operation;
        std::lock_guard<std::mutex> lock(mutex);
        totalSum += result;
    }

    std::string directory;
    int threadCount;
    double totalSum = 0;
    std::mutex mutex;
};

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <directory> <threadCount>\n";
        return 1;
    }
    std::string directory = argv[1];
    int threadCount = std::stoi(argv[2]);
    FileProcessor fileProcessor(directory, threadCount);
    fileProcessor.processFiles();
    return 0;
}