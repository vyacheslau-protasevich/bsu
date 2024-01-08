# Lab 6 OS

This project is a continuation of the task from Lab 3, but it has been updated to adhere to the C++11 standard. The code is designed to generate an array of random numbers, then separate the numbers into two categories: negative numbers that are multiples of three, and positive numbers. The numbers are then recombined into a new array with the negative numbers first, followed by the positive numbers.

## Changes from Previous Version

The previous version of this code was written using the Windows API for thread management and synchronization. In this updated version, we have switched to using the C++11 standard library for these tasks. Here are the main changes:

1. The Windows API functions for thread management (`CreateThread`, `WaitForSingleObject`, `SetEvent`, etc.) have been replaced with their C++11 counterparts (`std::thread`, `std::condition_variable::wait`, `std::condition_variable::notify_one`, etc.).

2. The Windows API `CRITICAL_SECTION` has been replaced with `std::mutex` from the C++11 standard library for mutual exclusion.

3. The `Sleep` function from the Windows API has been replaced with `std::this_thread::sleep_for` from the C++11 standard library.

4. The `DWORD WINAPI` thread function signature has been replaced with a simple `void` function. The thread functions no longer return a value; instead, one of them modifies a global variable (`count`) protected by a mutex.

## Building and Running

This project uses CMake for building. The minimum required version of CMake is 3.27. The project is set to use the C++11 standard.

To build and run the project, use the following commands in a terminal:

```bash
mkdir build
cd build
cmake ..
make
./lab_6_os
```

During the execution, the program will prompt you to enter the size of the array to be generated, the interval for element processing (in milliseconds), and a number X. The purpose of X is not used in the current version of the program.