# PHILOSOFERS_42

PHILOSOFERS is a project part of the School 42 curriculum. It simulates the dining philosophers problem, which is a classic synchronization problem. The project involves managing multiple threads representing philosophers who alternately think, eat, and sleep.

## Introduction

The dining philosophers problem is a classic computer science problem used to illustrate synchronization issues and techniques for resolving them. In this project, we simulate a number of philosophers sitting at a table, where each philosopher alternates between thinking, eating, and sleeping. The philosophers need forks to eat, and there are fewer forks than philosophers, which leads to potential deadlocks and starvation problems that need to be managed.

## Features

- Simulates the dining philosophers problem.
- Uses multithreading to manage philosophers.
- Implements synchronization mechanisms to avoid deadlocks and starvation.

## Requirements

- GCC or any C compiler.
- pthread library for thread management.

## Installation

Clone the repository and navigate to the project directory:

```bash
git clone git@github.com:oumimoun/1337-Philosophers.git
cd 1337-Philosophers
cd philo
```

Compile the program:

```bash
make
```

## Usage

Run the compiled program:

```bash
./philo 2 800 200 300 10
```

You can adjust the number of philosophers and other parameters.
