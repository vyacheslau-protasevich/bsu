# Dining Philosophers Problem Solution

This repository contains a C++ solution for the classic concurrency problem known as the Dining Philosophers problem.

## Problem Statement

The Dining Philosophers problem is a classic demonstration of a common computing problem - concurrency. Five silent philosophers sit at a round table with bowls of spaghetti. Forks are placed between each pair of adjacent philosophers. Each philosopher must alternately think and eat. However, a philosopher can only eat spaghetti when they have both left and right forks. Each fork can be held by only one philosopher and so a philosopher can use the fork only if it is not being used by another philosopher. After an individual philosopher finishes eating, they need to put down both forks so that the forks become available to others. A philosopher can take the fork on their right or the one on their left as they become available, but cannot start eating before getting both forks.

## Solution

The solution uses the C++ `std::binary_semaphore` to represent the forks. Each philosopher is represented as a separate thread. The philosophers acquire and release the forks (semaphores) as they eat and think.

## Code Structure

The code is structured as follows:

- `main.cpp`: This file contains the main function which initializes the philosophers (threads) and the forks (semaphores). It also starts the philosophers' routine of thinking and eating.

## How to Run

To compile and run the program, use the following commands:

```bash
g++ -std=c++20 -o philosophers main.cpp -pthread
./philosophers