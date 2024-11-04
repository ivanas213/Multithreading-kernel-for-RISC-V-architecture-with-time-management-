#include "../h/riscv.hpp"
#include "../h/MemoryAllocator.h"
#include "../h/thread.hpp"
#include "../lib/console.h"
#include "../h/sem.h"
using Body = void(*)(void*);   // Defining a type alias for a function pointer that takes void* and returns void.

// Function to pop the supervisor status and jump to the address stored in 'ra'.
void Riscv::popSppSpie() {
    __asm__ volatile("csrw sepc,ra");  // Set the supervisor exception program counter (sepc) to the return address (ra).
    __asm__ volatile("sret");          // Return from the trap, restoring the previous privilege mode and state.
}

// Function to handle supervisor traps (interrupts or exceptions).
void Riscv::handleSupervisorTrap() {

    volatile uint64 cause = r_scause();     // Get the cause of the trap.
    cause = cause & (0xffffffffffffffff);   // Mask the cause (only relevant bits are kept).
    
    // If the cause is a syscall (codes 0x8 or 0x9)
    if (cause == 0x0000000000000008UL || cause == 0x0000000000000009UL) {
        w_sip(0);   // Clear supervisor software interrupt pending bit.
        uint64 function;   // Variable to hold the syscall function code.
        
        // Move the value from register a0 (which holds the syscall number) to the 'function' variable.
        __asm__ volatile("mv %0,a0" : "=r"(function));  

        // Handling different system call cases based on the syscall number in 'function'.
        switch (function) {
            
            // Case for memory allocation syscall (function code 0x01).
            case(0x01): {
                volatile uint64 sepc = r_sepc() + 4;    // Move the program counter to the next instruction (skip syscall).
                volatile uint64 sstatus = r_sstatus();  // Save the supervisor status.
                
                size_t sz;   // Variable to hold the requested memory size.
                __asm__ volatile("ld s1, 11*8(fp)");  // Load the memory size from stack frame.
                __asm__ volatile("mv %0,s1" : "=r"(sz));  // Move it to sz.
                
                volatile void* ret = MemoryAllocator::getMemoryAllocator().mem_alloc(sz);  // Allocate memory.
                __asm__ volatile("mv a0,%[param]" :: [param]"r"(ret));  // Return the allocated memory address in register a0.
                
                w_sstatus((uint64)sstatus);  // Restore the supervisor status.
                w_sepc((uint64)sepc);  // Restore the program counter.
                break;
            }
            
            // Case for memory free syscall (function code 0x02).
            case(0x02): {
                volatile uint64 sepc = r_sepc() + 4;  // Move to the next instruction.
                volatile uint64 sstatus = r_sstatus();  // Save the supervisor status.
                
                void** addr;  // Pointer to the memory to be freed.
                __asm__ volatile("ld s1, 11*8(fp)");  // Load the memory address from the stack frame.
                __asm__ volatile("mv %[param],s1" : [param]"=r"(addr));  // Move it to addr.
                
                int ret = MemoryAllocator::getMemoryAllocator().mem_free(*addr);  // Free the memory.
                __asm__ volatile("mv a0,%[param]" :: [param]"r"(ret));  // Return success/failure in register a0.
                
                w_sstatus((uint64)sstatus);  // Restore the supervisor status.
                w_sepc((uint64)sepc);  // Restore the program counter.
                break;
            }

            // Case for thread creation syscall (function code 0x11).
            case(0x11): {
                volatile uint64 sepc = r_sepc() + 4;  // Move to the next instruction.
                volatile uint64 sstatus = r_sstatus();  // Save the supervisor status.
                
                thread_t* myHandle;  // Thread handle.
                Body body;  // Function pointer for the thread's body.
                void* arg;  // Argument for the thread's body.
                
                // Load thread handle, function pointer, and argument from the stack frame.
                __asm__ volatile("ld s1, 11*8(fp)");
                __asm__ volatile("mv %[param],s1" : [param]"=r"(myHandle));
                __asm__ volatile("ld s2, 12*8(fp)");
                __asm__ volatile("mv %[param],s2" : [param]"=r"(body));
                __asm__ volatile("ld s3, 13*8(fp)");
                __asm__ volatile("mv %[param],s3" : [param]"=r"(arg));

                // Create the thread.
                int ret = TCB::threadCreate(myHandle, body, arg) ? 0 : -1;
                __asm__ volatile("mv a0,%[param]" :: [param]"r"(ret));  // Return success/failure.
                
                w_sstatus((uint64)sstatus);  // Restore the supervisor status.
                w_sepc((uint64)sepc);  // Restore the program counter.
                break;
            }

            // Other syscall cases like thread exit (0x12), thread yield (0x13), semaphore operations (0x21-0x24), etc.
            // Each case follows a similar pattern: adjusting the program counter, handling the syscall, and restoring state.

            // Case for handling console input (function code 0x41).
            case 0x41: {
                volatile uint64 sepc = r_sepc() + 4;  // Move to the next instruction.
                volatile uint64 sstatus = r_sstatus();  // Save the supervisor status.

                char ret = __getc();  // Get a character from the console.
                __asm__ volatile("mv a0,%[param]" :: [param]"r"(ret));  // Return the character in register a0.
                
                w_sstatus((uint64)sstatus);  // Restore the supervisor status.
                w_sepc((uint64)sepc);  // Restore the program counter.
                break;
            }

            // Case for handling console output (function code 0x42).
            case 0x42: {
                volatile uint64 sepc = r_sepc() + 4;  // Move to the next instruction.
                volatile uint64 sstatus = r_sstatus();  // Save the supervisor status.

                char ch;
                __asm__ volatile("ld s1, 11*8(fp)");  // Load the character to be printed from the stack frame.
                __asm__ volatile("mv %0,s1" : "=r"(ch));  // Move it to ch.

                __putc(ch);  // Output the character to the console.
                w_sstatus((uint64)sstatus);  // Restore the supervisor status.
                w_sepc((uint64)sepc);  // Restore the program counter.
                break;
            }
        }
    }
    else if (cause == 0x8000000000000001UL) {
        mc_sip(SIP_SSIP);  // Handle software interrupt (SIP_SSIP).
    }
    else if (cause == 0x8000000000000009UL) {
        volatile uint64 sepc = r_sepc();  // Save the program counter.
        volatile uint64 sstatus = r_sstatus();  // Save the supervisor status.
        
        console_handler();  // Handle the console interrupt.
        
        w_sstatus((uint64)sstatus);  // Restore the supervisor status.
        w_sepc((uint64)sepc);  // Restore the program counter.
    }
    else {
        // Handle other cases (not explicitly defined).
    }
}
