#include <semaphore>
#include <thread>
#include <vector>
#include <iostream>
#include <chrono>

std::binary_semaphore fork[5] = { std::binary_semaphore(1), std::binary_semaphore(1), std::binary_semaphore(1), std::binary_semaphore(1), std::binary_semaphore(1) };

void philosopher(int i) {
    while (true) {
        std::cout << "Philosopher " << i+1 << " is thinking.\n";
        std::this_thread::sleep_for(std::chrono::seconds(2));
        fork[i].acquire();
        fork[(i + 1) % 5].acquire();

        std::cout << "Philosopher " << i+1 << " is eating, using forks " << i+1 << " and " << (i + 1) % 5 +1<< ".\n";
        std::this_thread::sleep_for(std::chrono::seconds(2));

        fork[i].release();
        fork[(i + 1) % 5].release();
    }
}

void philosopher4() {
    while (true) {
        std::cout << "Philosopher 5 is thinking.\n";
        std::this_thread::sleep_for(std::chrono::seconds(2));
        fork[0].acquire();
        fork[4].acquire();

        std::cout << "Philosopher 5, is eating using forks 1 and 5s.\n";
        std::this_thread::sleep_for(std::chrono::seconds(2));

        fork[0].release();
        fork[4].release();
    }
}

int main() {
    std::vector<std::thread> philosophers;

    for (int i = 0; i < 4; ++i) {
        philosophers.push_back(std::thread(philosopher, i));
    }

    philosophers.push_back(std::thread(philosopher4));

    for (auto& t : philosophers) {
        t.join();
    }

    return 0;
}
