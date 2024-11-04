#ifndef _syscall_h_
#define _syscall_h_

#include "../lib/hw.h"  // Includes hardware-specific definitions.
#include "riscv.hpp"    // Includes RISC-V register and instruction management.

void* _mem_alloc(size_t size);  // Allocates memory of given size.
int _mem_free(void* v);         // Frees previously allocated memory at pointer `v`.

class _thread;  // Forward declaration for thread type.

typedef _thread* thread_t;  // Alias for thread pointer type.

// Creates a new thread that starts at `start_routine` with argument `arg`.
int thread_create(thread_t* handle, void(*start_routine)(void*), void* arg);

// Initializes a thread without starting execution.
void thread_make(thread_t* handle, void(*start_routine)(void*), void* arg);

// Exits the current thread.
int thread_exit();

// Switches the current thread to another in the scheduling queue.
void thread_dispatch();

class _sem;  // Forward declaration for semaphore type.

typedef _sem* sem_t;  // Alias for semaphore pointer type.

// Opens a semaphore with an initial value `init`.
int sem_open(sem_t* handle, unsigned init);

// Closes a semaphore, releasing its resources.
int sem_close(sem_t handle);

// Decrements the semaphore and possibly blocks the calling thread.
int sem_wait(sem_t id);

// Increments the semaphore and potentially unblocks a waiting thread.
int sem_signal(sem_t id);

const int EOF = -1;  // End-of-file constant, typically used in input/output functions.

// Reads a character from input.
char getc();

// Writes a character to output.
void putc(char);

#endif

