#include "../h/scheduler.hpp"
#include "../h/thread.hpp"
#include "../h/printing.hpp"

// Define the static member 'readyQueue', which holds the list of ready threads.
List<TCB> Scheduler::readyQueue;

// The 'get()' function retrieves the next thread from the ready queue.
TCB *Scheduler::get() {
    TCB* thr = readyQueue.peekFirst();  // Check the first thread in the queue without removing it.
    
    // If there is more than one thread in the queue and the first thread is idle (has no body),
    // take the second thread in the queue and remove it.
    if(readyQueue.counter != 1 && thr->body == nullptr) {
       thr = readyQueue.removeSecond();  // Remove the second thread from the queue.
    }
    else {
        readyQueue.removeFirst();  // Remove the first thread from the queue if it's not idle or is the only thread.
    }
    
    return thr;  // Return the retrieved thread.
}

// The 'put()' function adds a thread to the ready queue.
void Scheduler::put(TCB* ccb) {
    readyQueue.addLast(ccb);  // Add the thread to the end of the queue.
}
