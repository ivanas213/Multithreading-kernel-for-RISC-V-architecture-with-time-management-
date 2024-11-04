#include "../h/sem.h"
#include "../h/MemoryAllocator.h"

// Function to create and open a new semaphore with an initial value.
Sem* Sem::open(int init) {
    return new Sem(init);  // Allocate memory for the new semaphore and initialize it with the given value.
}

// Function to close a semaphore and unblock any waiting threads.
int Sem::close(Sem* sem) {
    // While there are threads waiting (semaphore value ≤ 0), unblock them and move them to the ready queue.
    while (sem->getVal() <= 0 && sem->getWaiting().peekFirst()) {
        sem->incVal();  // Increment the semaphore value to indicate availability.
        sem->getWaiting().peekFirst()->unblock();  // Unblock the first waiting thread.
        Scheduler::put(sem->getWaiting().removeFirst());  // Move the unblocked thread to the scheduler's ready queue.
    }
    return 0;  // Return success.
}

// Function to perform a wait operation on the semaphore.
int Sem::wait() {
    value--;  // Decrease the semaphore value (indicating resource usage).
    // If the value is less than 0, block the current thread and put it in the waiting queue.
    if (value < 0) {
        waiting.addLast(TCB::running);  // Add the current thread to the waiting queue.
        TCB::running->block();  // Block the current running thread.
        TCB::yield();  // Yield control to another thread.
    }
    return 0;  // Return success.
}

// Function to perform a signal operation on the semaphore.
int Sem::signal() {
    value++;  // Increase the semaphore value (indicating resource release).
    // If there are waiting threads (value <= 0), unblock the first thread in the waiting queue.
    if (value <= 0) {
        waiting.peekFirst()->unblock();  // Unblock the first waiting thread.
        Scheduler::put(waiting.removeFirst());  // Move the unblocked thread to the scheduler's ready queue.
    }
    return 0;  // Return success.
}

// Overloaded new operator for Sem class to allocate memory using the custom memory allocator.
void* Sem::operator new(size_t sz) {
    MemoryAllocator m = MemoryAllocator::getMemoryAllocator();  // Get the memory allocator instance.
    Sem* s = (Sem*)m.mem_alloc(sz);  // Allocate memory for the semaphore.
    return s;  // Return the allocated memory.
}

// Overloaded delete operator for Sem class to free memory using the custom memory allocator.
void Sem::operator delete(void* v) {
    MemoryAllocator::getMemoryAllocator().mem_free(v);  // Free the memory allocated for the semaphore.
}
