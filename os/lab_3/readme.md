# Lab 3 OS

This project is a multi-threaded application written in C++ that demonstrates the use of events and critical sections for thread synchronization. The application creates an array of integers, either entered by the user or randomly generated, and performs various operations on this array using separate threads.

## Project Structure

The project consists of the following files:

- `CMakeLists.txt`: This file is used by CMake to handle the project's build process.
- `main.cpp`: This is the main file of the project where the `main` function resides.
- `main_tests.cpp`: This file contains the tests for the `main.cpp` file.

## How it Works

The application uses three threads: `main`, `work`, and `CountElement`.

### Main Thread

The main thread performs the following actions:

- Initializes the necessary events and critical sections.
- Creates an array of integers, the size and elements of which are entered by the user or randomly generated.
- Outputs the size and elements of the original array to the console.
- Asks the user for a time interval required for rest after preparing one element in the array.
- Starts the `work` thread.
- Starts the `CountElement` thread.
- Asks for a number X.
- Notifies the `work` and `CountElement` threads about the start of work (using an event with manual reset).
- Receives a signal from the `work` thread about the output of the array (using event 2).
- Outputs the result of the `work` thread's work to the screen.
- Waits for a signal from the `CountElement` thread (using a critical section).
- Outputs the result of the `CountElement` thread's work to the screen.

### Work Thread

The `work` thread performs the following actions:

- Waits for a signal from the `main` thread about the start of work (using an event with manual reset).
- Searches the array for negative elements that are multiples of 3 (places them in a new array on the left, the rest of the array elements - on the right).
- Rests for a specified time interval after each prepared element.
- Notifies the `main` thread about the output of the work results (the launch moment will occur after the final array is formed (using event 2)).

### CountElement Thread

The `CountElement` thread performs the following actions (for synchronization with the `main` thread, use an event with manual reset and a critical section):

- Waits for a signal from the `main` thread about the start of work (using an event with manual reset).
- Counts the number of non-negative elements = X, in the initial array.
- Notifies the `main` thread about the output of the result (using a critical section).

## Building and Running the Project

This project uses CMake for building. To build and run the project, follow these steps:

1. Navigate to the project directory.
2. Create a new directory called `build` and navigate into it: `mkdir build && cd build`.
3. Run `cmake ..` to generate the build files.
4. Run `make` to build the project.
5. Run the executable: `./lab_3_os`.

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