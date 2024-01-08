#include <iostream>
#include <vector>
#include <thread>
#include <mutex>

class Matrix {
public:
    Matrix(int rows, int cols) : data(rows, std::vector<double>(cols, 0)) {}

    std::vector<double>& operator[](int index) {
        return data[index];
    }

    const std::vector<double>& operator[](int index) const {
        return data[index];
    }

    int rows() const {
        return data.size();
    }

    int cols() const {
        return data[0].size();
    }

private:
    std::vector<std::vector<double>> data;
};

class ThreadSafeCounter {
public:
    ThreadSafeCounter(int maxCount) : count(0), maxCount(maxCount) {}

    int increment() {
        std::lock_guard<std::mutex> lock(mutex);
        return count < maxCount ? count++ : -1;
    }

private:
    std::mutex mutex;
    int count;
    int maxCount;
};

void matrixProductThread(const Matrix& A, const Matrix& B, Matrix& C, ThreadSafeCounter& counter) {
    int index;
    while ((index = counter.increment()) != -1) {
        int i = index / C.cols();
        int j = index % C.cols();
        for (int k = 0; k < A.cols(); k++) {
            C[i][j] += A[i][k] * B[k][j];
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

Matrix multiplyMatrices(const Matrix& A, const Matrix& B, int threadCount) {
    Matrix C(A.rows(), B.cols());
    ThreadSafeCounter counter(A.rows() * B.cols());

    std::vector<std::thread> threads;
    for (int i = 0; i < threadCount; i++) {
        threads.push_back(std::thread(matrixProductThread, std::ref(A), std::ref(B), std::ref(C), std::ref(counter)));
    }

    for (auto& thread : threads) {
        thread.join();
    }

    return C;
}

void writeToFile(const Matrix& C, const std::string& filename) {
    std::ofstream file(filename, std::ios::app);
    for (int i = 0; i < C.rows(); i++) {
        for (int j = 0; j < C.cols(); j++) {
            file << C[i][j] << " ";
        }
        file << "\n";
    }
    file.close();
}

void printMatrix(const Matrix& C) {
    for (int i = 0; i < C.rows(); i++) {
        for (int j = 0; j < C.cols(); j++) {
            std::cout << C[i][j] << " ";
        }
        std::cout << "\n";
    }
}