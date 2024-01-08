#include <Windows.h>
#include <iostream>
#include <vector>
#include <chrono>
#include <random>



std::vector<int> findNegativeNumbersDivisibleBy6(std::vector<int>* arr) {
    std::vector<int> result;
    for (int num : *arr) {
        if (num < 0 && num % 6 == 0) {
            result.push_back(num);
        }
    }
    return result;
}

DWORD WINAPI FindNegativeNumbersBy6(LPVOID lpParam) {
    auto start_time = std::chrono::high_resolution_clock::now();
    std::cout << "Worker thread started at " << start_time.time_since_epoch().count() << " ms." << std::endl;
    std::vector<int>* arr = reinterpret_cast<std::vector<int>*>(lpParam);
    std::cout << "Negative number divided by 6: ";

    std::vector<int> negativeNumbers = findNegativeNumbersDivisibleBy6(arr);
    for (int num : negativeNumbers) {
        std::cout << num << ' ';
        Sleep(5);
    }

    auto stop_time = std::chrono::high_resolution_clock::now();
    std::cout << "\nWorker thread stopped at " << stop_time.time_since_epoch().count() << " ms." << std::endl;

    return 0;
}

int generate_random_number() {
    int min = 0;
    int max = 10;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> disForArraySize(min, max);
    return disForArraySize(gen);
}

std::vector<int> generate_random_array(int size) {
    int min = -100;
    int max = 100;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> disForArrayNumbers(min, max);
    std::vector<int> myArray;
    for (int i = 0; i < size; i++) {
        myArray.push_back(disForArrayNumbers(gen) * 10);
    }
    return myArray;
}


#ifndef TESTING
int main() {
    int k = generate_random_number();
    std::cout << "Number of elements: " << k << '\n';
    std::vector<int> myArray = generate_random_array(k);
    for (int i = 0; i < k; i++) {
        std::cout << myArray[i] << ' ';
    }
    std::cout << '\n';

    HANDLE workerThread = CreateThread(nullptr, 0, FindNegativeNumbersBy6, &myArray, 0, nullptr);
    if (workerThread == nullptr) {
        std::cerr << "Thread creation failed." << std::endl;
        return 1;
    }

    DWORD suspendCount = SuspendThread(workerThread);
    if (suspendCount == (DWORD)-1) {
        std::cerr << "Thread suspension failed." << std::endl;
        CloseHandle(workerThread);
        auto stop_time = std::chrono::high_resolution_clock::now();
        std::cout << "Worker thread stopped at " << stop_time.time_since_epoch().count() << " ms." << std::endl;
        return 1;
    }


    std::cout << '\n';
    DWORD resumeCount = ResumeThread(workerThread);
    if (resumeCount == (DWORD)-1) {
        std::cerr << "Thread resumption failed." << std::endl;
        CloseHandle(workerThread);
        auto stop_time = std::chrono::high_resolution_clock::now();
        std::cout << "Worker thread stopped at " << stop_time.time_since_epoch().count() << " ms." << std::endl;
        return 1;
    }
  //  WaitForSingleObject(workerThread, INFINITE);

    CloseHandle(workerThread);
//    CloseHandle(countThread);
    return 0;
}
#endif