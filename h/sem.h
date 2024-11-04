#ifndef _sem_h_
#define _sem_h_

#include "../h/syscall_c.h"  // Includes system call definitions.
#include "../h/scheduler.hpp" // Includes the scheduler to manage thread scheduling.
#include "../h/thread.hpp"    // Includes the Thread Control Block (TCB) class.
#include "../h/list.hpp"      // Includes the List class to manage waiting threads.

class Sem {
private:
    Sem(int v) : value(v) {}  // Private constructor initializes the semaphore value.

    List<TCB> waiting;        // List of TCBs waiting for the semaphore to become available.
    int value = 0;            // Semaphore's current value, managing resource access.

public:
    // Decrements the semaphore value; blocks the thread if value < 0.
    int wait();

    // Increments the semaphore value; unblocks a waiting thread if any exist.
    int signal();

    // Returns the current value of the semaphore.
    int getVal() {
        return value;
    }

    // Increases the semaphore value by one.
    void incVal() {
        value++;
    }

    // Returns the list of threads waiting on the semaphore.
    List<TCB> getWaiting() {
        return waiting;
    }

    // Opens a semaphore with an initial value.
    static Sem* open(int init);

    // Closes the semaphore, freeing its resources.
    static int close(Sem* sem);

    // Overloads the new operator for custom memory allocation.
    static void* operator new(size_t);

    // Overloads the delete operator for custom memory deallocation.
    static void operator delete(void* v);
};

#endif

