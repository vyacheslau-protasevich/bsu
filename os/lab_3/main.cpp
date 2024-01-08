#include <iostream>
#include <windows.h>
#include <cstdlib> // For functions rand() and srand()
#include <vector>

const int MAX_SIZE = 100;

CRITICAL_SECTION cs;
HANDLE event1, event2;

std::vector<int> generateArray(int arraySize) {
    std::vector<int> array(arraySize);
    srand(static_cast<unsigned int>(time(0)));
    for (int i = 0; i < arraySize; ++i) {
        array[i] = rand() % 100 - 50; // Generating random numbers from -50 to 49
    }
    return array;
}

DWORD WINAPI WorkThread(LPVOID param) {
    std::vector<int>* array = static_cast<std::vector<int>*>(param);
    WaitForSingleObject(event1, INFINITE);

    int newArray[MAX_SIZE];
    int negativeMultipleOfThree[MAX_SIZE]; // New array for negative elements, multiples of 3
    int positiveElements[MAX_SIZE]; // Array for positive elements
    int negCount = 0; // Counter for negative elements, multiples of 3
    int posCount = 0; // Counter for positive elements

    for (int i = 0; i < array->size(); ++i) {
        Sleep(100);
        if ((*array)[i] < 0 && (*array)[i] % 3 == 0) {
            negativeMultipleOfThree[negCount++] = (*array)[i];
        } else {
            positiveElements[posCount++] = (*array)[i];
        }
    }

    for (int i = 0; i < negCount; ++i) {
        newArray[i] = negativeMultipleOfThree[i];
    }
    // Copying positive elements to the main array
    for (int i = 0; i < posCount; ++i) {
        newArray[negCount + i] = positiveElements[i];
    }
    SetEvent(event2);

    return 0;
}

DWORD WINAPI CountElementThread(LPVOID param) {
    std::vector<int>* array = static_cast<std::vector<int>*>(param);
    WaitForSingleObject(event1, INFINITE);

    int count = 0;
    EnterCriticalSection(&cs);
    for (int i = 0; i < array->size(); ++i) {
        if ((*array)[i] >= 0) {
            ++count;
        }
    }
    LeaveCriticalSection(&cs);

    return count;
}

#ifndef TEST
int main() {
    InitializeCriticalSection(&cs);
    event1 = CreateEvent(NULL, TRUE, FALSE, NULL);
    event2 = CreateEvent(NULL, FALSE, FALSE, NULL);

    std::cout << "Enter array size: ";
    int arraySize;
    std::cin >> arraySize;

    std::vector<int> array = generateArray(arraySize);

    std::cout << "Generated array elements:" << std::endl;
    for (int i = 0; i < arraySize; ++i) {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;

    HANDLE workThread = CreateThread(NULL, 0, WorkThread, &array, 0, NULL);
    HANDLE countThread = CreateThread(NULL, 0, CountElementThread, &array, 0, NULL);

    SetEvent(event1);

    WaitForSingleObject(event2, INFINITE);

    std::cout << "Result from work thread: ";
    for (int i = 0; i < arraySize; ++i) {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;

    DWORD count;
    GetExitCodeThread(countThread, &count);
    EnterCriticalSection(&cs); // Entering the critical section for safe output of the result
    std::cout << "Number of non-negative elements: " << count << std::endl;
    LeaveCriticalSection(&cs); // Leaving the critical section

    CloseHandle(event1);
    CloseHandle(event2);
    CloseHandle(workThread);
    CloseHandle(countThread);
    DeleteCriticalSection(&cs);

    return 0;
}
#endif