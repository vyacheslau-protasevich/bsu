#include <iostream>
#include <cstdlib> // For functions rand() and srand()
#include <thread>
#include <condition_variable>
#include <mutex>

std::condition_variable cv1, cv2;
std::mutex mtx1, mtx2, mtx3;
const int MAX_SIZE = 100;

int array[MAX_SIZE];
int newArray[MAX_SIZE];
int arraySize;
int interval;
int X;
int count = 0;


void WorkThread() {
    std::unique_lock<std::mutex> lock(mtx1);
    cv1.wait(lock);

    int negativeMultipleOfThree[MAX_SIZE]; // New array for negative elements divisible by 3
    int positiveElements[MAX_SIZE]; // Array for positive elements
    int negCount = 0; // Counter for negative elements divisible by 3
    int posCount = 0; // Counter for positive elements

    for (int i = 0; i < arraySize; ++i) {
        std::this_thread::sleep_for(std::chrono::milliseconds(interval));
        if (array[i] < 0 && array[i] % 3 == 0) {
            negativeMultipleOfThree[negCount++] = array[i];
        } else {
            positiveElements[posCount++] = array[i];
        }
    }

    for (int i = 0; i < negCount; ++i) {
        newArray[i] = negativeMultipleOfThree[i];
    }
    // Copying positive elements to the main array
    for (int i = 0; i < posCount; ++i) {
        newArray[negCount + i] = positiveElements[i];
    }
    cv2.notify_one();
}

void CountElementThread() {
    std::unique_lock<std::mutex> lock(mtx1);
    cv1.wait(lock);

    mtx3.lock();
    for (int i = 0; i < arraySize; ++i) {
        if (array[i] >= 0) {
            ++count;
        }
    }
    mtx3.unlock();
}

int main() {
    std::cout << "Enter array size: ";
    std::cin >> arraySize;

    // Initializing the random number generator
    srand(static_cast<unsigned int>(time(0)));

    std::cout << "Generated array elements:" << std::endl;
    for (int i = 0; i < arraySize; ++i) {
        array[i] = rand() % 100 - 50; // Generating random numbers from -50 to 49
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "Enter the interval for element processing (in milliseconds): ";
    std::cin >> interval;

    std::thread workThread(WorkThread);
    std::thread countThread(CountElementThread);

    std::cout << "Enter number X: ";
    std::cin >> X;

    cv1.notify_all();

    std::unique_lock<std::mutex> lock(mtx2);
    cv2.wait(lock);

    std::cout << "Result from work thread: ";
    for (int i = 0; i < arraySize; ++i) {
        std::cout << newArray[i] << " ";
    }
    std::cout << std::endl;

    mtx3.lock();
    std::cout << "Number of non-negative elements: " << count << std::endl;
    mtx3.unlock();

    workThread.join();
    countThread.join();

    return 0;
}
