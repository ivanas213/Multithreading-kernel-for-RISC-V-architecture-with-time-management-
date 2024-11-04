#include "../h/syscall_c.h"
#include "../h/thread.hpp"
extern  void userMain(void* );    // Declaration of an external function that serves as the entry point for the user-defined main function.

int main(){

    Riscv::w_stvec((uint64) &Riscv::supervisorTrap);  // Set the trap handler for supervisor mode by writing the address of supervisorTrap to the stvec register.
    Riscv::ms_sstatus(Riscv::SSTATUS_SPIE);           // Enable interrupts in supervisor mode by setting the SPIE bit in the sstatus register.

    TCB* thread[2];                                   // Array to hold two thread control block (TCB) pointers.
    thread_t* mainThread=new thread_t ();              // Create a new thread_t object for the main thread.
    thread_t* userMainThread=new thread_t ();          // Create a new thread_t object for the userMain thread.
    
    thread[0]= TCB::threadCreate(mainThread, nullptr, nullptr); // Create the main thread, passing a null function pointer and arguments (assumed to be a system thread).
    thread[1]= TCB::threadCreate(userMainThread, userMain, nullptr); // Create the userMain thread, passing the userMain function pointer and null arguments.
    
    TCB::running=thread[0];                           // Set the main thread as the currently running thread.
    TCB::yield();                                     // Yield the CPU to allow another thread (userMain) to run.

    return 0;                                         // Program exit.
}
