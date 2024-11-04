#include "../h/thread.hpp"
#include "../h/MemoryAllocator.h"

// Static member initialization
TCB* TCB::running = nullptr;  // Pointer to the currently running thread

// Yield control of the current thread to allow another thread to run
void TCB::yield() {
    // Save the current state of the thread (push all registers)
    Riscv::pushRegisters();
    // Dispatch the next thread to run
    TCB::dispatch();
    // Restore the registers of the new running thread
    Riscv::popRegisters();
}

// Dispatching a new thread to run by switching contexts
void TCB::dispatch() {
    TCB* oldC = running;  // Save the currently running thread

    // If the old thread is not finished and not blocked, re-add it to the scheduler
    if (!oldC->isFinished() && !oldC->blocked) {
        Scheduler::put(oldC);
    }
    // Get the next thread from the scheduler
    running = Scheduler::get();
    // Perform a context switch from the old thread to the new running thread
    contextSwitch(&oldC->context, &running->context);
}

// Creates a new thread and schedules it if the body is valid
TCB* TCB::threadCreate(thread_t *mh, Body b, void *a) {
    TCB* t = new TCB(mh, b, a);  // Create a new thread

    // If the thread has a valid body, put it in the scheduler
    if (t->body != nullptr)
        Scheduler::put(t);
    
    return t;  // Return the created thread
}

// Exit the current thread by marking it as finished and yielding control
int TCB::exit() {
    running->finished = true;  // Mark the current thread as finished
    yield();  // Yield control to another thread
    return 0;  // Return success
}

// Wrapper function for executing the thread's body
void TCB::threadWrapper() {
    // If the running thread has no body, return control to the previous thread state
    if (running->body == nullptr) {
        Riscv::popSppSpie();  // Pop state register values
    }
    // Execute the thread's body function
    running->body(running->arg);
    // Mark the thread as finished after executing the body
    running->setFinished(true);
    // Yield control to another thread after finishing execution
    TCB::yield();
}

// Overloading the new operator to use custom memory allocation for TCB objects
void *TCB::operator new(size_t sz) {
    MemoryAllocator m = MemoryAllocator::getMemoryAllocator();  // Get memory allocator instance
    TCB* t = (TCB*)m.mem_alloc(sz);  // Allocate memory for TCB
    return t;
}

// Overloading the delete operator to use custom memory deallocation for TCB objects
void TCB::operator delete(void *v) {
    MemoryAllocator::getMemoryAllocator().mem_free(v);  // Free the memory
}

// Create a thread without scheduling it (just creation)
TCB* TCB::justCreate(thread_t *mh, TCB::Body b, void *a) {
    return new TCB(mh, b, a);  // Create a new thread but do not add it to the scheduler
}
