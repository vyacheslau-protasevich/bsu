# Lab 1 OS

This project is a simple demonstration of thread management in C++. It creates an array of integers, either inputted from the console or randomly generated. A worker thread is then created and managed to perform operations on this array.

## Features

- Generation of an array of integers, either through console input or random generation.
- Creation of a worker thread that performs operations on the array.
- Ability to suspend and resume the worker thread.
- Waiting for the worker thread to finish its operations.
- Displaying the result of the worker thread's operations on the console.
- Proper termination of the program after all operations are done.

## Additional Task

The program also includes a function that prints out negative elements in the array that are divisible by 6. After each iteration, the program sleeps for 5 milliseconds before continuing. This function is also run in the worker thread and the program waits for this task to complete before terminating.

## `task_98.cpp`

This file contains a C++98 compatible program that finds all negative numbers divisible by 6 in a given array. The program uses a separate worker thread to perform the calculation and print the results. The main thread creates the worker thread, suspends it, resumes it, and then waits for it to finish.

The program consists of three main functions:

- `findNegativeNumbersDivisibleBy6(std::vector<int>* arr)`: This function takes a pointer to a vector of integers as input and returns a vector of all negative integers in the input vector that are divisible by 6.

- `FindNegativeNumbersBy6(LPVOID lpParam)`: This is the worker thread function. It takes a pointer to a vector of integers, finds all negative numbers divisible by 6, and prints them.

- `main()`: This function prompts the user to enter a number of elements and then the elements themselves. It then creates a worker thread to find and print all negative numbers divisible by 6 in the entered elements.

## How it works

The main function generates a random number `k` which is used as the size of the array. The array is then filled with random numbers ranging from -1000 to 1000. 

A worker thread is created using the `CreateThread` function. This thread executes the `FindNegativeNumbersBy6` function, which finds all negative numbers in the array that are divisible by 6 and prints them to the console.

The worker thread is then suspended using the `SuspendThread` function. After a brief pause, the thread is resumed using the `ResumeThread` function. 

The program waits for the worker thread to finish its operations before terminating.

## Testing

Unit tests are an integral part of this project to ensure the functionality of the individual components. They help to verify if the individual units of the source code are working as expected.

To run the unit tests, navigate to the test directory and execute the test files. Make sure you have a suitable unit testing framework installed on your system.

Please note that the tests should be updated as and when the source code is modified. This ensures that the new changes integrate well with the existing code and the functionality of the application remains intact.

## Building and Running

This project uses CMake for building. The minimum required version of CMake is 3.27.

To build the project, navigate to the project directory and run the following commands:

```bash
mkdir build
cd build
cmake ..
make
