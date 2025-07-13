# Philosopher Project - 42 School

## Table of Contents
1.  [Introduction](#introduction)
2.  [Project Overview](#project-overview)
3.  [Mandatory Part Learnings](#mandatory-part-learnings)
4.  [Bonus Part Learnings](#bonus-part-learnings)
5.  [Benefits of the Project](#benefits-of-the-project)
6.  [Challenges and Problems Faced](#challenges-and-problems-faced)
7.  [How to Run the Project](#how-to-run-the-project)
8.  [Example Usage](#example-usage)
9.  [Contributing](#contributing)
10. [Acknowledgments](#acknowledgments)

## 1. Introduction

This `README.md` file documents the Philosopher project, a classic problem in concurrent programming, undertaken as part of the 42 School curriculum. This project challenges students to implement a solution to the Dining Philosophers problem, focusing on synchronization, thread management, and avoiding deadlocks and race conditions.

## 2. Project Overview

The Dining Philosophers problem is a classic multi-process synchronization problem. Imagine five philosophers sitting around a circular table. In front of each philosopher is a plate of spaghetti. Between each pair of philosophers is a single fork. To eat, a philosopher needs two forks: one from their left and one from their right. The challenge is to design a protocol that ensures all philosophers can eventually eat without deadlocking (where no one can eat) or starving (where some philosophers never get to eat).

This project required the use of POSIX threads (pthreads) and mutexes to manage shared resources (forks) and synchronize the actions of the philosophers.

## 3. Mandatory Part Learnings

The mandatory part of this project laid the foundational understanding of multi-threading and synchronization in C. Here's what I learned:

* **Thread Creation and Management (pthreads):** Gained practical experience in creating, joining, and detaching threads using the `pthread_create()`, `pthread_join()`, and `pthread_detach()` functions. Understanding the lifecycle of a thread was crucial.
* **Mutexes for Mutual Exclusion:** Deep dive into `pthread_mutex_init()`, `pthread_mutex_lock()`, `pthread_mutex_unlock()`, and `pthread_mutex_destroy()`. This was fundamental to protecting critical sections and preventing race conditions when accessing shared resources (like forks).
* **Preventing Race Conditions:** Learned to identify and eliminate race conditions by correctly using mutexes to ensure that only one thread can access a shared resource at a time.
* **Basic Synchronization Concepts:** Understood the need for synchronization in concurrent programming to maintain data integrity and predictable program behavior.
* **Time Management (usleep, gettimeofday):** Used `usleep()` for simulating philosopher actions (eating, sleeping, thinking) and `gettimeofday()` for precise time tracking to meet project requirements (e.g., time to die, time to eat, time to sleep).
* **Error Handling:** Implemented robust error checking for pthread functions to ensure the program behaves correctly under various conditions.
* **Program Argument Parsing:** Handled command-line arguments to configure the simulation parameters (number of philosophers, time to die, time to eat, time to sleep, optional number of times each philosopher must eat).

## 4. Bonus Part Learnings

The bonus part extended the project to include more advanced synchronization mechanisms and considerations:

* **Semaphores (Optional/Advanced):** If implemented, explored the use of semaphores (`sem_init`, `sem_wait`, `sem_post`, `sem_destroy`) as an alternative or complementary synchronization primitive to mutexes, particularly for resource counting.
* **More Complex Deadlock Prevention Strategies:** While the mandatory part typically uses a basic strategy (e.g., odd/even philosopher picking order), the bonus might have involved exploring or implementing more sophisticated algorithms like banker's algorithm principles or specific hierarchical locking.
* **Performance Optimization:** Considerations for minimizing lock contention and improving the efficiency of the simulation.
* **Philosopher Must Eat X Times:** Implementing the condition where the simulation stops after each philosopher has eaten a certain number of times introduced additional synchronization challenges and state management.
* **Visualizer/Debugging Tools:** (If you attempted this) Exploring tools or techniques to visualize the state of the philosophers and forks, aiding in debugging complex synchronization issues.

## 5. Benefits of the Project

This project offered significant benefits for my development as a programmer:

* **Deep Understanding of Concurrency:** Provided a hands-on, practical understanding of multi-threading, concurrent execution, and the challenges they present.
* **Mastery of Synchronization Primitives:** Solidified my knowledge and practical application of mutexes (and potentially semaphores), which are critical tools for building robust concurrent applications.
* **Problem-Solving Skills:** Forced me to think critically about resource allocation, deadlock prevention, and starvation avoidance strategies.
* **Debugging Complex Systems:** Improved my debugging skills significantly, as race conditions and deadlocks are notoriously difficult to track down. Learning to use tools like `gdb` with multi-threaded applications was invaluable.
* **Foundation for Distributed Systems:** The concepts learned here are directly applicable to understanding and building more complex distributed systems.
* **Real-world Applicability:** The Dining Philosophers problem, while abstract, represents real-world scenarios in operating systems, databases, and network programming where multiple processes or threads compete for shared resources.

## 6. Challenges and Problems Faced

Despite the benefits, this project presented several significant hurdles:

* **Deadlock Prevention:** The most significant challenge was ensuring the simulation never deadlocked. Initially, simple approaches often led to deadlocks. Iterating on the fork acquisition strategy (e.g., requiring philosophers to pick up the left fork then the right, or imposing an order like odd philosophers pick left then right, even philosophers pick right then left) was crucial.
* **Race Conditions:** Even after preventing deadlocks, subtle race conditions could lead to incorrect behavior (e.g., philosophers reporting eating at the same time without holding both forks). Meticulous mutex placement was required.
* **Starvation:** Ensuring that no philosopher waited indefinitely to eat was another tricky aspect. Some solutions that prevent deadlock might inadvertently lead to starvation.
* **Debugging Multi-threaded Code:** Debugging concurrent programs is inherently difficult. Tracing execution flow, identifying which thread holds which lock, and pinpointing the exact moment a bug occurs was challenging. Extensive use of print statements and learning to use `gdb` with threads was essential.
* **Precise Timing:** Meeting the `time_to_die`, `time_to_eat`, and `time_to_sleep` requirements accurately, especially with multiple threads, required careful management of `usleep` and time calculations.
* **Off-by-One Errors in Logic:** Small logical errors in mutex locking/unlocking or state transitions could have cascading and difficult-to-diagnose effects.

## 7. How to Run the Project

To compile and run the Philosopher project, follow these steps:

**Prerequisites:**
* A C compiler (e.g., GCC)
* Make

**Compilation:**

Clone the repository (if applicable) and navigate to the project directory.
```bash
git clone <your-repository-url>
cd philosopher