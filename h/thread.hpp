#ifndef _thread_hpp_
#define _thread_hpp_

#include "../lib/hw.h"           // Include hardware-level definitions.
#include "scheduler.hpp"         // Include the Scheduler class for thread management.
#include "syscall_c.h"           // Include system call declarations.
#include "riscv.hpp"             // Include RISC-V specific implementations for thread operations.

// Thread Control Block (TCB) class manages individual threads and their states.
class TCB
{
public:
    static void* operator new (size_t);         // Allocates memory for a TCB instance.
    static void operator delete (void* v);      // Deallocates memory for a TCB instance.
    ~TCB() { stack = nullptr; }                 // Destructor, cleans up resources.

    bool isFinished() const { return finished; } // Returns if the thread is finished.
    void setFinished(bool value) { finished = value; } // Sets the thread's finished state.

    using Body = void (*)(void*);               // Defines a thread body type alias for functions with a void* parameter.

    static void yield();                        // Temporarily yields execution of the running thread.
    static TCB *running;                        // Pointer to the currently running thread.

    static TCB* threadCreate(thread_t* mh, Body b, void* a); // Creates and initializes a new thread.
    static TCB* justCreate(thread_t* mh, Body b, void* a);   // Initializes a thread without starting it.
    static int exit();                          // Marks the current thread for exit.

    static void sleep(time_t time);             // Suspends thread execution for a specified duration.
    void block() { blocked = true; }            // Blocks the thread from execution.
    void unblock() { blocked = false; }         // Unblocks the thread for execution.

private:
    friend Scheduler;                           // Allows Scheduler to access private members.
    
    // Constructor initializes the thread with handle, body, and arguments.
    TCB(thread_t* myHandle, Body body, void* arg) :
        body(body), arg(arg), myHandle(myHandle),
        stack(body != nullptr ? new uint64[DEFAULT_STACK_SIZE] : nullptr),
        context({body != nullptr ? (uint64) &threadWrapper : 0,
                 stack != nullptr ? (uint64) &stack[DEFAULT_STACK_SIZE] : 0}),
        finished(false) {}

    struct Context
    {
        uint64 ra;                              // Return address register.
        uint64 sp;                              // Stack pointer register.
    };
    bool blocked = false;                       // Indicates if the thread is blocked.
    Body body;                                  // Function pointer for the thread's body.
    void* arg;                                  // Argument to be passed to the thread body.
    thread_t* myHandle;                         // Pointer to the thread handle.
    uint64 *stack;                              // Stack allocated for the thread.
    Context context;                            // Context structure for saving thread state.
    bool finished;                              // Indicates if the thread has finished execution.
    bool error = false;                         // Indicates if an error has occurred.

    static void contextSwitch(Context *oldContext, Context *runningContext); // Switches context between threads.
    static void dispatch();                     // Selects and starts the next thread for execution.
    static void threadWrapper();                // Wraps and starts the thread's body function.
};

#endif
