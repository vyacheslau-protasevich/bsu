#include <windows.h>
#include <iostream>
#include <vector>

std::vector<int> findNegativeNumbersDivisibleBy6(std::vector<int>* arr) {
    std::vector<int> result;
    for (std::vector<int>::iterator it = arr->begin(); it != arr->end(); ++it) {
        if (*it < 0 && *it % 6 == 0) {
            result.push_back(*it);
        }
    }
    return result;
}

DWORD WINAPI FindNegativeNumbersBy6(LPVOID lpParam) {
    std::cout << "Worker thread started." << std::endl;
    std::vector<int>* arr = reinterpret_cast<std::vector<int>*>(lpParam);
    std::cout << "Negative number divided by 6: ";

    std::vector<int> negativeNumbers = findNegativeNumbersDivisibleBy6(arr);
    for (std::vector<int>::iterator it = negativeNumbers.begin(); it != negativeNumbers.end(); ++it) {
        std::cout << *it << ' ';
        Sleep(5);
    }

    std::cout << "\nWorker thread stopped." << std::endl;

    return 0;
}

int main() {
    int k;
    std::cout << "Enter the number of elements: ";
    std::cin >> k;

    std::vector<int> myArray(k);
    std::cout << "Enter " << k << " numbers: ";
    for (int i = 0; i < k; i++) {
        std::cin >> myArray[i];
    }

    HANDLE workerThread = CreateThread(NULL, 0, FindNegativeNumbersBy6, &myArray, 0, NULL);
    if (workerThread == NULL) {
        std::cerr << "Thread creation failed." << std::endl;
        return 1;
    }

    DWORD suspendCount = SuspendThread(workerThread);
    if (suspendCount == (DWORD)-1) {
        std::cerr << "Thread suspension failed." << std::endl;
        CloseHandle(workerThread);
        std::cout << "Worker thread stopped." << std::endl;
        return 1;
    }

    DWORD resumeCount = ResumeThread(workerThread);
    if (resumeCount == (DWORD)-1) {
        std::cerr << "Thread resumption failed." << std::endl;
        CloseHandle(workerThread);
        std::cout << "Worker thread stopped." << std::endl;
        return 1;
    }

    WaitForSingleObject(workerThread, INFINITE);

    CloseHandle(workerThread);
    return 0;
}
