# Lab 2 OS

This project is a console application that involves two processes: a Parent process and a Child process. The Parent process creates the Child process and passes an array of integers to it. The Child process then processes this array, printing out any negative elements that are divisible by 6. After each iteration, the Child process sleeps for 5 milliseconds before continuing.

## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes.

### Prerequisites

- A C++ compiler (GCC, Clang, MSVC, etc.)
- An IDE (CLion, Visual Studio, etc.)

### Installing

1. Clone the repository to your local machine.
2. Open the project in your preferred IDE.
3. Build the project.

## Testing

Unit tests are an integral part of this project to ensure the functionality of the individual components. They help to verify if the individual units of the source code are working as expected.

To run the unit tests, navigate to the test directory and execute the test files. Make sure you have a suitable unit testing framework installed on your system.

Please note that the tests should be updated as and when the source code is modified. This ensures that the new changes integrate well with the existing code and the functionality of the application remains intact.

## Running the tests

The project includes a set of unit tests for the `processNumber` function in the Child process. These tests can be run using the Google Test framework.

## Built With

- C++ - The main programming language used.
- Google Test - The testing framework used.

## Code Overview

### Child Process

The Child process is defined in `child.cpp`. It includes a function `processNumber` that takes an integer as input and prints it if it's negative and divisible by 6. The `main` function in this file processes command line arguments as integers and passes them to `processNumber`.

### Parent Process

The Parent process is defined in `parent.cpp`. It includes a function `startChild` that creates the Child process with a specific console color attribute and passes an array of integers to it. The `main` function in this file generates a random array of integers and passes it to `startChild`.

### Data Structures

- `STARTUPINFO`: This structure is used to specify the window station, desktop, standard handles, and appearance of the main window for a process at creation time.
- `PROCESS_INFORMATION`: This structure is filled in by `CreateProcess` with information about the newly created process, such as its process and thread identifiers.

## License

This project is licensed under the MIT License.
