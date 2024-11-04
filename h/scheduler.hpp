#ifndef _scheduler_hpp_
#define _scheduler_hpp_

#include "list.hpp" 

class TCB; // Forward declaration of the TCB class, allowing it to be referenced before it's fully defined.

class Scheduler {
private:
    static List<TCB> readyQueue; // Static linked list (readyQueue) for storing tasks (TCBs) ready to execute.

public:
    // Adds a TCB (task control block) to the readyQueue.
    static void put(TCB* ccb);

    // Retrieves a TCB from the readyQueue.
    static TCB* get();
};

#endif
