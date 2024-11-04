#include "../h/syscall_cpp.hpp"

// Overloading global new operator to use custom memory allocation
void* operator new (size_t size) {
    return _mem_alloc(size);  // Allocate memory using the system call
};

// Overloading global delete operator to use custom memory deallocation
void operator delete (void* v) {
    _mem_free(v);  // Free memory using the system call
};

// Overloading global new[] operator for array allocations
void *operator new[](size_t n) {
    return _mem_alloc(n);  // Allocate memory for array using the system call
}

// Overloading global delete[] operator for array deallocations
void operator delete[] (void* v) {
    _mem_free(v);  // Free array memory using the system call
}

// Overloading new operator specifically for Thread objects
void *Thread::operator new(size_t sz) {
    return _mem_alloc(sz);  // Allocate memory for a Thread object
}

// Overloading delete operator specifically for Thread objects
void Thread::operator delete(void *v) {
    _mem_free(v);  // Free memory of a Thread object
}

// Overloading new[] operator specifically for arrays of Thread objects
void *Thread::operator new[](size_t sz) {
    return _mem_alloc(sz);  // Allocate memory for an array of Thread objects
}

// Overloading delete[] operator specifically for arrays of Thread objects
void Thread::operator delete[](void *v) {
    _mem_free(v);  // Free memory of an array of Thread objects
}

// Method to start the thread by creating it using a system call
void Thread::start() {
    thread_create(&myHandle, &wrapper, this);  // Create thread and pass the wrapper function as the entry point
}

// Constructor to create a thread with a specific body function and argument
Thread::Thread(void (*body)(void *), void *arg) {
    thread_make(&this->myHandle, body, arg);  // Create the thread using the body and arg
}

// Default constructor for a thread
Thread::Thread() {
    myHandle = 0;  // Initialize thread handle to 0
}

// Destructor for the Thread class, noexcept ensures that no exceptions are thrown
Thread::~Thread() noexcept {
    myHandle = 0;  // Set thread handle to 0 upon destruction
}

// Method to trigger a thread dispatch (context switch)
void Thread::dispatch() {
    thread_dispatch();  // Perform thread dispatch using system call
}

// Static wrapper method used as the entry point for threads
void Thread::wrapper(void *t) {
    Thread* thread = (Thread*)t;  // Cast the void pointer to a Thread object
    thread->run();  // Call the run method of the Thread object
}

// Constructor for Semaphore, opens a semaphore with initial value
Semaphore::Semaphore(unsigned int init) {
    sem_open(&myHandle, init);  // Create a semaphore with an initial value
}

// Method to wait on a semaphore
void Semaphore::wait() {
    sem_wait(myHandle);  // Perform semaphore wait using system call
}

// Method to signal a semaphore
void Semaphore::signal() {
    sem_signal(myHandle);  // Perform semaphore signal using system call
}

// Destructor for Semaphore, closes the semaphore upon destruction
Semaphore::~Semaphore() {
    sem_close(myHandle);  // Close the semaphore using system call
}

// Overloading new operator specifically for Semaphore objects
void *Semaphore::operator new(size_t sz) {
    return _mem_alloc(sz);  // Allocate memory for a Semaphore object
}

// Overloading delete operator specifically for Semaphore objects
void Semaphore::operator delete(void *v) {
    _mem_free(v);  // Free memory of a Semaphore object
}

// Overloading new[] operator specifically for arrays of Semaphore objects
void *Semaphore::operator new[](size_t sz) {
    return _mem_alloc(sz);  // Allocate memory for an array of Semaphore objects
}

// Overloading delete[] operator specifically for arrays of Semaphore objects
void Semaphore::operator delete[](void *v) {
    _mem_free(v);  // Free memory of an array of Semaphore objects
}

// Method to get a character from input (console)
char Console::getc() {
    return ::getc();  // Use the system call to get a character
}

// Method to output a character to the console
void Console::putc(char c) {
    ::putc(c);  // Use the system call to output a character
}
