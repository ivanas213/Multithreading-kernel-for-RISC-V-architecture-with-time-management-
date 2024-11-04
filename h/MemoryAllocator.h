#ifndef _mem_alloc_cpp_
#define _mem_alloc_cpp_

#include "../lib/hw.h"
#include "syscall_c.h"
#include "printing.hpp"

// Structure representing a memory block in the allocator
struct Mem{
    size_t size;   // Size of the memory block
    Mem* next;     // Pointer to the next memory block in the linked list
    bool free;     // Flag indicating if the block is free (true) or allocated (false)
};

// Class implementing a singleton memory allocator for managing a heap area
class MemoryAllocator {
private:
    MemoryAllocator();   // Private constructor for singleton pattern

    static Mem* head;    // Pointer to the first memory block in the allocator

public:
    static MemoryAllocator memoryAllocator;  // Singleton instance of the allocator
    static MemoryAllocator getMemoryAllocator(); // Method to get the singleton instance

    // Method to allocate a memory block of the specified size
    void* mem_alloc(size_t size);

    // Method to free an allocated memory block
    int mem_free(void* base);
};

#endif
