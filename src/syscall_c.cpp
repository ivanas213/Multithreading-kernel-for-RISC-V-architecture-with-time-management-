#include "../h/syscall_c.h"
#include "../h/MemoryAllocator.h"

// Function to allocate memory using a system call
void * _mem_alloc(size_t size) {
    uint64 call = 0x01;  // System call identifier for memory allocation

    // Pass the size parameter to the system call
    __asm__ volatile ("mv a1, %[param]"::[param]"r"(size));

    // Pass the system call identifier
    __asm__ volatile("mv a0,%[param]"::[param]"r"(call));
    __asm__ volatile("ecall");  // Make the system call

    // Retrieve the result of the system call (the allocated memory address)
    void *returnval;
    __asm__ volatile("mv %[param],a0":[param]"=r"(returnval));
    return (char*) returnval;  // Return the allocated memory address
};

// Function to free memory using a system call
int _mem_free(void* base){
    uint64 call = 0x02;  // System call identifier for memory freeing
    Mem** addr = (Mem**) &base;

    // Pass the base address to the system call
    __asm__ volatile("mv a1,%[param]"::[param]"r"(addr));

    // Pass the system call identifier
    __asm__ volatile("mv a0,%[param]"::[param]"r"(call));
    __asm__ volatile("ecall");  // Make the system call

    // Retrieve the result of the system call
    int returnval;
    __asm__ volatile("mv %[param],a0":[param]"=r"(returnval));
    return returnval;  // Return the status of the memory freeing operation
}

// Function to create a new thread using a system call
int thread_create (thread_t* handle, void(*start_routine)(void*), void* arg) {
    uint64 call = 0x11;  // System call identifier for thread creation

    // Pass the function arguments (handle, start_routine, arg) to the system call
    __asm__ volatile("mv a3,%[param]"::[param]"r"(arg));
    __asm__ volatile("mv a2,%[param]"::[param]"r"(start_routine));
    __asm__ volatile("mv a1,%[param]"::[param]"r"(handle));
    
    // Pass the system call identifier
    __asm__ volatile("mv a0,%[param]"::[param]"r"(call));
    __asm__ volatile("ecall");  // Make the system call

    // Retrieve the result of the system call
    int ret = -1;
    __asm__ volatile("mv %[param],a0":[param]"=r"(ret));
    return ret;  // Return the result (thread creation status)
}

// Function to make a thread using a system call (without return value)
void thread_make(thread_t* handle, void(*start_routine)(void*), void* arg) {
    uint64 call = 0x14;  // System call identifier for thread making

    // Pass the function arguments (handle, start_routine, arg) to the system call
    __asm__ volatile("mv a3,%[param]"::[param]"r"(arg));
    __asm__ volatile("mv a2,%[param]"::[param]"r"(start_routine));
    __asm__ volatile("mv a1,%[param]"::[param]"r"(handle));

    // Pass the system call identifier
    __asm__ volatile("mv a0,%[param]"::[param]"r"(call));
    __asm__ volatile("ecall");  // Make the system call
}

// Function to exit a thread using a system call
int thread_exit() {
    uint64 call = 0x12;  // System call identifier for thread exit

    // Pass the system call identifier
    __asm__ volatile("mv a0,%[param]"::[param]"r"(call));
    __asm__ volatile("ecall");  // Make the system call

    // Retrieve the result of the system call
    int ret = -1;
    __asm__ volatile("mv %[param],a0":[param]"=r"(ret));
    return ret;  // Return the result (thread exit status)
}

// Function to trigger a context switch using a system call
void thread_dispatch() {
    uint64 call = 0x13;  // System call identifier for thread dispatch

    // Pass the system call identifier
    __asm__ volatile("mv a0,%[param]"::[param]"r"(call));
    __asm__ volatile("ecall");  // Make the system call
}

// Function to open a semaphore using a system call
int sem_open (sem_t* handle, unsigned init) {
    uint64 call = 0x21;  // System call identifier for semaphore opening

    // Pass the semaphore handle and initial value to the system call
    __asm__ volatile("mv a2,%[param]"::[param]"r"(init));
    __asm__ volatile("mv a1,%[param]"::[param]"r"(handle));

    // Pass the system call identifier
    __asm__ volatile("mv a0,%[param]"::[param]"r"(call));
    __asm__ volatile("ecall");  // Make the system call

    // Retrieve the result of the system call
    int ret = -1;
    __asm__ volatile("mv %[param],a0":[param]"=r"(ret));
    return ret;  // Return the result (semaphore creation status)
}

// Function to close a semaphore using a system call
int sem_close (sem_t handle) {
    uint64 call = 0x22;  // System call identifier for semaphore closing

    // Pass the semaphore handle to the system call
    __asm__ volatile("mv a1,%[param]"::[param]"r"(&handle));

    // Pass the system call identifier
    __asm__ volatile("mv a0,%[param]"::[param]"r"(call));
    __asm__ volatile("ecall");  // Make the system call

    // Retrieve the result of the system call
    int ret = -1;
    __asm__ volatile("mv %[param],a0":[param]"=r"(ret));
    return ret;  // Return the result (semaphore closing status)
}

// Function to wait on a semaphore using a system call
int sem_wait (sem_t id) {
    uint64 call = 0x23;  // System call identifier for semaphore wait

    // Pass the semaphore ID to the system call
    __asm__ volatile("mv a1,%[param]"::[param]"r"(&id));

    // Pass the system call identifier
    __asm__ volatile("mv a0,%[param]"::[param]"r"(call));
    __asm__ volatile("ecall");  // Make the system call

    // Retrieve the result of the system call
    int ret = -1;
    __asm__ volatile("mv %[param],a0":[param]"=r"(ret));
    return ret;  // Return the result (wait operation status)
}

// Function to signal a semaphore using a system call
int sem_signal (sem_t id) {
    uint64 call = 0x24;  // System call identifier for semaphore signal

    // Pass the semaphore ID to the system call
    __asm__ volatile("mv a1,%[param]"::[param]"r"(&id));

    // Pass the system call identifier
    __asm__ volatile("mv a0,%[param]"::[param]"r"(call));
    __asm__ volatile("ecall");  // Make the system call

    // Retrieve the result of the system call
    int ret = -1;
    __asm__ volatile("mv %[param],a0":[param]"=r"(ret));
    return ret;  // Return the result (signal operation status)
}

// Function to read a character from input using a system call
char getc () {
    uint64 call = 0x41;  // System call identifier for reading a character

    // Pass the system call identifier
    __asm__ volatile("mv a0,%[param]"::[param]"r"(call));
    __asm__ volatile("ecall");  // Make the system call

    // Retrieve the character read from input
    char ret = -1;
    __asm__ volatile("mv %[param],a0":[param]"=r"(ret));
    return ret;  // Return the character
}

// Function to print a character to output using a system call
void putc (char c) {
    uint64 call = 0x42;  // System call identifier for printing a character

    // Pass the character to be printed to the system call
    __asm__ volatile("mv a1,%[param]"::[param]"r"(c));

    // Pass the system call identifier
    __asm__ volatile("mv a0,%[param]"::[param]"r"(call));
    __asm__ volatile("ecall");  // Make the system call
}
