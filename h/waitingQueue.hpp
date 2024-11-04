#ifndef _waiting_queue_hpp_
#define _waiting_queue_hpp_
#include "../lib/hw.h"

/**
 * Generic Queue class template for storing elements with priorities.
 * Each element is stored in the form of a node with data, priority, and a pointer to the next node.
 */
template<typename T>
class Queue {
private:
    struct Elem {
        T* data;            // Pointer to the data element
        Elem* next;         // Pointer to the next element in the queue
        time_t priority;    // Priority of the element

        // Element constructor to initialize data, next pointer, and priority.
        Elem(T* d, Elem* e, time_t p) : data(d), next(e), priority(p) {}
    };

    Elem* head = nullptr;  // Pointer to the first element in the queue
    Elem* tail = nullptr;  // Pointer to the last element in the queue

public:
    /**
     * Adds an element to the queue based on its priority.
     * Elements are added in ascending order of priority.
     *
     * @param d Pointer to the data to be added.
     * @param p Priority of the new element.
     */
    void addElem(T* d, time_t p) {
        Elem* prev = nullptr;
        Elem* tek = nullptr;

        // Traverse to find the correct position based on priority
        for (tek = head, prev = nullptr; tek; prev = tek, tek = tek->next) 
            if (tek->priority >= p) break;

        // Create new element with the provided data and priority
        Elem* elem = new Elem(d, nullptr, p);

        if (prev) 
            prev->next = elem;  // Insert in the middle or end
        else 
            head = elem;        // Insert as the first element

        elem->next = tek;

        if (head)
            elem->priority = p - head->priority;  // Update priority relative to the head

        if (!elem->next) 
            tail = elem;        // Update tail if inserted at the end
    }

    /**
     * Removes and returns the first element in the queue.
     * If the queue is empty, returns nullptr.
     *
     * @return Pointer to the removed element's data or nullptr if empty.
     */
    T* removeFirst() {
        if (!head) return nullptr;

        time_t prior = head->priority;

        if (head->next)
            head->next->priority -= prior;  // Adjust the next element's priority

        Elem* t = head;
        head = head->next;

        t = nullptr;  // Deallocate removed element
        return t;
    }
};

#endif
