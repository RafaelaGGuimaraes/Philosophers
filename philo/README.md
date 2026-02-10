*This project has been created as part of the 42 curriculum by rgomes-g.*

# Philosophers

## Description

The **Philosophers** project is a simulation of the classic *Dining Philosophers Problem*, a well-known concurrency and synchronization challenge in computer science. The goal of the project is to implement a multi-threaded program in C where a number of philosophers sit around a table, alternating between thinking, eating, and sleeping.

Each philosopher must take two forks (shared resources) to eat. The main challenge of the project is to manage concurrent access to these shared resources using mutexes, avoiding common issues such as **deadlocks, race conditions, and starvation**, while ensuring that no philosopher dies from not eating within a specified time.

The program monitors the state of each philosopher in real time and stops the simulation if a philosopher dies or if all philosophers have eaten the required number of times (when applicable).

---

## Instructions

### Compilation

To compile the project, run:

make

This will generate the executable:

./philo

### Execution

The program must be executed with the following arguments:

./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]

#### Example:

./philo 5 800 200 200

This means:

* 5 philosophers
* They die if they don’t eat within 800ms
* Eating takes 200ms
* Sleeping takes 200ms

Optional:

./philo 5 800 200 200 7

In this case, the simulation stops when all philosophers have eaten at least 7 times.

### Cleaning files

To remove object files:

make clean

To remove object files and the executable:

make fclean

To recompile from scratch:

make re

---

## Features

* Multi-threaded implementation using **pthread**
* Synchronization using **mutexes**
* Accurate time tracking in milliseconds
* Safe and synchronized logging of philosopher actions
* Death detection and simulation termination
* Optional meal limit per philosopher

---

## Technical Choices

* Each philosopher is represented by a thread.
* Forks are implemented as mutexes to prevent simultaneous use.
* A separate monitoring mechanism checks if any philosopher has died.
* All prints are protected by a mutex to avoid mixed output.
* Time is managed using precise timestamps based on the start of the simulation.

---

## Resources

### References Used

* POSIX Threads (pthread) documentation
* Mutex and concurrency tutorials in C
* 42 Network project subject: *Philosophers*

### Use of AI

AI tools were used for:

* Understanding and clarifying concurrency concepts (threads, mutexes, race conditions).
* Helping structure and organize this README file.
* Explaining logic behind synchronization strategies.

AI was **not used to generate the final source code of the project**, but rather as a learning and explanatory aid.