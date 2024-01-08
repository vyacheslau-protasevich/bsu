# Lab 4 OS

This project is a console application that simulates the interaction between multiple processes: a Boss process, Parent processes, and Child processes. The communication between these processes is modeled using five events (with automatic reset) that represent messages "A", "B", "C", "D", and the end of the session for Parent and Child processes.

## Getting Started

To get started with this project, clone the repository and open the project in your preferred C++ IDE (the project was developed using CLion 2023.3.2).

## Prerequisites

This project is developed using C++. Make sure you have a C++ compiler installed on your system.

## Running the Project

To run the project, navigate to the project directory and run the `main.cpp` file.

## Project Description

### Boss Process

The Boss process is responsible for:

- Initializing synchronization objects.
- Asking the user for the number of Parent and Child processes (<=4) to start.
- Asking for the number of messages to be sent/received by all Parent and Child processes.
- Starting the specified number of Parent and Child processes.
- Receiving messages from the console and sending them to the Child processes in a separate thread.
- Receiving messages from the Parent processes and displaying them on the console.
- Receiving end-of-session messages from the Parent and Child processes.
- Terminating its operation.

### Parent Process

The Parent process is responsible for:

- Synchronizing the operation of the Parent and Child processes using a semaphore.
- Implementing message passing using events.
- Receiving messages from the console consisting of "A" or "B" and sending them (one by one) to the Boss process.
- Sending an end-of-session message to the Boss process.
- Terminating its operation.

### Child Process

The Child process is responsible for:

- Synchronizing the operation of the Parent and Child processes using a semaphore.
- Implementing message passing using events.
- Receiving messages consisting of "C" or "D" from the Boss process and displaying them on the console.
- Sending an end-of-session message to the Boss process.
- Terminating its operation.

## Building and Running the Project

This project uses CMake for building. To build and run the project, follow these steps:

1. Navigate to the project directory.
2. Create a new directory called `build` and navigate into it: `mkdir build && cd build`.
3. Run `cmake ..` to generate the build files.
4. Run `make` to build the project.
5. Run the executable: `./lab_4_os`.

## Testing

Unit tests are an integral part of this project to ensure the functionality of the individual components. They help to verify if the individual units of the source code are working as expected.

To run the unit tests, navigate to the test directory and execute the test files. Make sure you have a suitable unit testing framework installed on your system.

Please note that the tests should be updated as and when the source code is modified. This ensures that the new changes integrate well with the existing code and the functionality of the application remains intact.

## Running the Tests

This project uses Google Test for testing. To run the tests, follow these steps:

1. Navigate to the `build` directory.
2. Run the test executable: `./main_tests`.

## License

This project is licensed under the MIT License.