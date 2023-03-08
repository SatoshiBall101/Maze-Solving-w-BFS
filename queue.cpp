/*
queue.cpp
*/

#include "queue.h"

//Constructor. maxlen must be as large as the total number
// of Locations that will ever be entered into this Queue.
Queue::Queue(int maxlen) {
    head = 0;
    tail = 0;
    // *** You complete **** CHECKPOINT 3
    // need storage!!
    
    contents = new Location[maxlen]; // dynamic allocation of queue

    for (int i = 0; i < maxlen; i++)
    {
      contents[i].row = -1;
      contents[i].col = -1;
      // initialize the queue with -1 in all elements (is this needed?)
    }

}

//Destructor. releases resources. C++ will call it automatically.
Queue::~Queue() {
    // *** You complete **** CHECKPOINT 3

    delete[] contents; // return mem to heap

}

//Insert a new Location at the end/back of our list
void Queue::add_to_back(Location loc) {

    // *** You complete **** CHECKPOINT 3

    contents[tail].row = loc.row;
    contents[tail].col = loc.col;
    tail++;
}

//Return and "remove" the oldest Location not already extracted
Location Queue::remove_from_front() {

    // *** You complete **** CHECKPOINT 3

    Location s;

    s.row = contents[head].row;
    s.col = contents[head].col;

    head++;
    return s;
}

//Is this Queue empty? (did we extract everything added?)
//This is complete, you don't need to change it.
bool Queue::is_empty() {
    return head == tail;
}

