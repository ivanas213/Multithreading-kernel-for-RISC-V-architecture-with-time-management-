#ifndef _syscall_cpp
#define _syscall_cpp

#include "syscall_c.h"  // Includes system call functions for OS interaction.

void* operator new (size_t);        // Allocates memory for a single object.
void operator delete (void* v);     // Frees memory of a single object.
void* operator new[] (size_t);      // Allocates memory for an array of objects.
void operator delete[] (void* v);   // Frees memory of an array of objects.

// Thread class provides functionality to create, manage, and control threads.
class Thread {
public:
    static void* operator new (size_t);        // Allocates memory for a Thread instance.
    static void operator delete (void* v);     // Frees memory of a Thread instance.
    static void* operator new[] (size_t);      // Allocates memory for an array of Thread instances.
    static void operator delete[] (void* v);   // Frees memory of an array of Thread instances.

    Thread(void (*body)(void*), void* arg);    // Initializes a thread with a function `body` and argument `arg`.
    virtual ~Thread();                         // Virtual destructor for cleanup.
    void start();                              // Starts the thread execution.
    static void dispatch();                    // Switches to another thread.
    static void sleep(time_t);                 // Suspends thread execution for a specified period.
    static void wrapper(void *t);              // Helper for executing a thread function.

protected:
    Thread();                                  // Protected constructor for inherited classes.
    virtual void run() {}                      // Function to override in derived classes for thread actions.

private:
    thread_t myHandle;                         // Handle to the underlying thread.
};

// Semaphore class provides synchronization primitives to control resource access.
class Semaphore {
public:
    static void* operator new (size_t);        // Allocates memory for a Semaphore instance.
    static void operator delete (void* v);     // Frees memory of a Semaphore instance.
    static void* operator new[] (size_t);      // Allocates memory for an array of Semaphore instances.
    static void operator delete[] (void* v);   // Frees memory of an array of Semaphore instances.

    Semaphore(unsigned init = 1);              // Initializes a semaphore with an initial count.
    virtual ~Semaphore();                      // Destructor to free resources.
    void wait();                               // Decrements semaphore and potentially blocks if <= 0.
    void signal();                             // Increments semaphore and potentially unblocks a thread.

private:
    sem_t myHandle;                            // Handle to the underlying semaphore.
};

// PeriodicThread class, for threads that require periodic activation.
class PeriodicThread : public Thread {
protected:
    PeriodicThread(time_t period);             // Constructor initializing thread with period.
    virtual void periodicActivation() {}       // To be overridden with periodic behavior.
};

// Console class provides basic console I/O functionality.
class Console {
public:
    static char getc();                        // Reads a character from the console.
    static void putc(char);                    // Writes a character to the console.
};

#endif
