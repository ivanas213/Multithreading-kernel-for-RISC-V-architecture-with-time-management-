// defines a template class List that implements a singly linked list
#ifndef _list_hpp_
#define _list_hpp_

template<typename T>
class List {
private:
    friend class Scheduler; // Allows the Scheduler class to access private members of List

    // Nested struct representing an element (node) in the linked list
    struct Elem {
        T *data;     // Pointer to the data of type T
        Elem *next;  // Pointer to the next element in the list

        // Constructor to initialize an element with data and next pointer
        Elem(T *data, Elem *next) : data(data), next(next) {}
    };

    Elem *head, *tail; // Pointers to the head and tail of the list
    int counter = 0;   // Counter to track the number of elements in the list

public:
    List() : head(0), tail(0) {} // Default constructor initializes an empty list

    // Disallow assignment operator for the List class
    List<T> &operator=(const List<T> &) = delete;

    // Adds a new element at the beginning of the list
    void addFirst(T *data)
    {
        Elem *elem = new Elem(data, head); // Create a new element with head as the next element
        head = elem;                       // Update head to the new element
        if (!tail) { tail = head; }        // If the list was empty, update tail to the new head
        counter++;                         // Increment the counter
    }

    // Adds a new element at the end of the list
    void addLast(T *data)
    {
        Elem *elem = new Elem(data, nullptr); // Create a new element with nullptr as the next element
        if (tail)
        {
            tail->next = elem;  // Link the last element to the new element
            tail = elem;        // Update tail to the new element
        } else
        {
            head = tail = elem; // If the list was empty, both head and tail point to the new element
        }
        counter++;              // Increment the counter
    }

    // Removes and returns the first element of the list
    T *removeFirst()
    {
        if (!head) { return 0; } // Return 0 if the list is empty

        Elem *elem = head;       // Store the current head
        head = head->next;       // Update head to the next element
        if (!head) { tail = 0; } // If the list is now empty, set tail to 0

        T *ret = elem->data;     // Store the data to return
        delete elem;             // Delete the old head element
        counter--;               // Decrement the counter
        return ret;              // Return the data
    }

    // Returns the first element's data without removing it
    T *peekFirst()
    {
        if (!head) { return 0; } // Return 0 if the list is empty
        return head->data;       // Return the data of the head element
    }

    // Removes and returns the last element of the list
    T *removeLast()
    {
        if (!head) { return 0; } // Return 0 if the list is empty

        Elem *prev = 0;          // Pointer to store the previous element
        for (Elem *curr = head; curr && curr != tail; curr = curr->next)
        {
            prev = curr;         // Traverse the list to find the last element
        }

        Elem *elem = tail;       // Store the current tail
        if (prev) { prev->next = 0; } // Set the second last element's next to 0
        else { head = 0; }       // If there was only one element, set head to 0
        tail = prev;             // Update tail to the second last element

        T *ret = elem->data;     // Store the data to return
        delete elem;             // Delete the old tail element
        counter--;               // Decrement the counter
        return ret;              // Return the data
    }

    // Returns the last element's data without removing it
    T *peekLast()
    {
        if (!tail) { return 0; } // Return 0 if the list is empty
        return tail->data;       // Return the data of the tail element
    }

    // Returns the current number of elements in the list
    int getCounter(){
        return counter;
    }

    // Removes and returns the element at a specified position
    T *removeFromPosition(int index){
        if(index >= counter || index <= 0) return nullptr; // Return nullptr if index is invalid

        int i = 0;               // Position counter
        Elem *tek, *prev = nullptr; // Temporary pointers for traversal
        for (tek = head; tek; prev = tek, tek = tek->next){
            if (i++ == index) break; // Stop at the specified index
        }

        prev->next = tek->next;       // Link previous element to the next element
        if (tek->next == nullptr) tail = tek; // Update tail if removing the last element
        T *ret = tek->data;           // Store the data to return
        delete tek;                   // Delete the element
        counter--;                    // Decrement the counter
        return ret;                   // Return the data
    }

    // Removes and returns the second element in the list
    T* removeSecond(){
        Elem* el = head->next;        // Pointer to the second element
        head->next = el->next;        // Update head's next to skip the second element
        if(counter-- == 2) tail = head; // Update tail if the list has only two elements
        T* ret = el->data;            // Store the data to return
        delete el;                    // Delete the second element
        return ret;                   // Return the data
    }
};

#endif
