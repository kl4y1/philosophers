*This project has been created as part of the 42 curriculum by mnajem.*

---

# Philosophers

## Description

**Philosophers** is a multithreading project from the 42 curriculum inspired by the famous *Dining Philosophers Problem*, introduced by Edsger Dijkstra.

The goal of this project is to understand how concurrent programs behave when multiple threads share limited resources. The simulation represents philosophers sitting around a table who continuously alternate between thinking, eating, and sleeping.

Each philosopher must acquire two forks shared with neighboring philosophers in order to eat. Without proper synchronization, this situation can easily lead to problems such as **deadlocks**, **race conditions**, or **starvation**.

This project focuses on designing a safe and deterministic simulation using POSIX threads and mutexes while respecting strict timing constraints and ensuring correct resource management.

The simulation ends when a philosopher dies or when all philosophers have eaten a specified number of times (if provided).

---

## Instructions

### Clone the Repository

git clone <repository_url>
cd philo

---

### Compilation

Compile the project using:

make

Available Makefile rules:

make        # compile the project  
make clean  # remove object files  
make fclean # remove object files and executable  
make re     # recompile everything  

After compilation, the executable `philo` will be created.

---

### Execution

Run the program using:

./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]

---

### Parameters

| Argument | Description |
|-----------|-------------|
| number_of_philosophers | Number of philosophers and forks |
| time_to_die | Time in milliseconds before a philosopher dies without eating |
| time_to_eat | Time spent eating |
| time_to_sleep | Time spent sleeping |
| number_of_times_each_philosopher_must_eat | *(optional)* Simulation stops once all philosophers have eaten enough |

---

### Example

./philo 5 800 200 200

Example output:

0 1 has taken a fork  
0 1 has taken a fork  
0 1 is eating  
200 1 is sleeping  
400 1 is thinking  

---

## Implementation Details

The simulation is implemented using:

- One thread per philosopher
- Mutex-protected forks
- Thread-safe printing system
- Shared simulation state
- Monitoring mechanism detecting philosopher death
- Accurate timestamp calculations
- Proper thread joining and mutex destruction

Special care was taken to prevent:

- deadlocks
- race conditions
- starvation
- undefined thread behavior

---

## Resources

### References

- Edsger Dijkstra — Dining Philosophers Problem
- POSIX Threads Programming Guide  
  https://man7.org/linux/man-pages/man7/pthreads.7.html
- pthread mutex documentation  
  https://man7.org/linux/man-pages/man3/pthread_mutex_lock.3.html
- Operating Systems: Three Easy Pieces (Concurrency chapters)

---

### AI Usage

AI tools were used strictly as learning assistants during development.  
They were mainly used for:

- understanding multithreading concepts
- clarifying synchronization strategies
- discussing architectural decisions
- improving documentation clarity

All implementation logic, synchronization handling, debugging, and final design decisions were implemented and validated manually.

---

## Learning Outcomes

Through this project, I gained practical experience with:

- multithreaded programming in C
- mutex synchronization
- concurrent resource sharing
- race condition debugging
- timing-sensitive simulations
- safe thread lifecycle management

---

## Author

**mnajem**  
42 Network Student