# Project Title: Inter-Process Communication via Anonymous Pipe in C++

This project consists of two console processes, `Server` and `Consume`, which exchange messages via an anonymous pipe. The descriptors of the pipe are inheritable.

At any given time, only one of the processes can transmit a message.

## Server Process

The `Server` process performs the following actions:

- Accepts the size and elements of an array from the console. The array is of type `char`.
- Launches the `Consume` process.
- Sends the size of the character array and its elements to the `Consume` process via the anonymous pipe.
- Receives a character array from the `Consume` process via the anonymous pipe.
- Displays the information sent and received via the pipe on the console.

## Consume Process

The `Consume` process performs the following actions:

- Receives the size of the character array and its elements from the `Server` process via the anonymous pipe.
- Displays the received data on the console.
- Identifies punctuation marks in the received data.
- Displays the identified punctuation marks on the console and sends them back to the `Server` process via the anonymous pipe.

## Getting Started

To get a local copy up and running, follow these steps:

1. Clone the repository.
2. Open the project in CLion 2023.3.2 or any other C++ IDE.
3. Build and run the `Server` process.

## Testing

Unit tests are an integral part of this project to ensure the functionality of the individual components. They help to verify if the individual units of the source code are working as expected.

To run the unit tests, navigate to the test directory and execute the test files. Make sure you have a suitable unit testing framework installed on your system.

Please note that the tests should be updated as and when the source code is modified. This ensures that the new changes integrate well with the existing code and the functionality of the application remains intact.

## Running Tests

To run the tests, follow these steps:

1. Open the project in CLion 2023.3.2 or any other C++ IDE.
2. Build and run the `runTests` target.

## Built With

- C++
- Google Test for unit testing

## License

This project is licensed under the MIT License.