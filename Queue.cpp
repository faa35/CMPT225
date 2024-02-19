/* 
 * Queue.cpp - Does not work well!
 *
 * Description: Array-based implementation of Queue as an ADT class
 * Class Invariant: Queue maintained in FIFO order
 *
 * Author:
 * Date:
 */
 
#include <iostream>
#include "Queue.h"

using std::cout;
using std::endl;

// Description: Constructor
Queue::Queue() {
    elements = new int[INITIAL_CAPACITY];
    capacity = INITIAL_CAPACITY;
    elementCount = 0;
    frontindex = 0;
    backindex = 0;
    
}

// Description: Inserts newElement at the back of Queue
// Time Efficiency: O(1)
// void Queue::enqueue(int newElement) {
//     elementCount++;
//     elements[backindex] = newElement;
//     backindex = (backindex + 1) % capacity;    
//     return;
// } 

// void Queue::enqueue(int newElement) {
//     if (elementCount == capacity) {  // If the array is full, double the capacity
//         int* newElements = new int[capacity * 2];
//         for (unsigned int i = 0; i < capacity; i++) {
//             newElements[i] = elements[(frontindex + i) % capacity];
//         }
//         delete[] elements;
//         elements = newElements;
//         frontindex = 0;
//         backindex = capacity;
//         capacity *= 2;
//     }
//     elements[backindex] = newElement;
//     backindex = (backindex + 1) % capacity;
//     elementCount++;
//     return;
// } 

//Queue(const Queue &rhs);
Queue::Queue(const Queue &rhs) {
    capacity = rhs.capacity;
    elementCount = rhs.elementCount;
    frontindex = rhs.frontindex;
    backindex = rhs.backindex;
    elements = new int[capacity];
    for (unsigned int i = 0; i < capacity; i++) {
        elements[i] = rhs.elements[i];
    }
}

//Queue& operator=(const Queue &rhs);
Queue& Queue::operator=(const Queue &rhs) {
    if (this != &rhs) {
        delete[] elements;
        capacity = rhs.capacity;
        elementCount = rhs.elementCount;
        frontindex = rhs.frontindex;
        backindex = rhs.backindex;
        elements = new int[capacity];
        for (unsigned int i = 0; i < capacity; i++) {
            elements[i] = rhs.elements[(frontindex + i)% rhs.capacity];
        }
    }
    return *this;
}




void Queue::enqueue(int newElement) {
    if ( ((frontindex == 0) && (backindex == capacity-1)) || (backindex == (frontindex-1 + capacity) % capacity) ){ // if the array is full   //(backindex == (frontindex-1) % capacity)
        // int* newElements = new int[capacity * 2];
        // for (unsigned int i = 0; i < capacity; i++) {
        //     newElements[i] = elements[(frontindex + i) % capacity];
        // }
        // delete[] elements;
        // elements = newElements;
        // frontindex = 0;
        // backindex = capacity;
        // capacity *= 2;
        // elements[backindex] = newElement;
        // elementCount++;

        //using the same thing using copy constructor and assignment operator
        Queue temp(*this);
        cout << "temp: " ;
        temp.printQueue();
        cout << endl;
        delete[] elements;
        capacity = temp.capacity * 2;
        elements = new int[capacity];

        for (unsigned int i = 0; i < temp.capacity; i++) {
            elements[i] = temp.elements[(frontindex + i) % temp.capacity];
        }

        frontindex = 0;
        backindex = temp.capacity;
        elements[backindex] = newElement;
        elementCount++;
    }
    
    else if ( elementCount == 0 ) { // if the array is empty
        elements[backindex] = newElement;
        // backindex is still 0
        elementCount++;
    }
    else if ( backindex == capacity-1 ) { // if the array is not full but backindex is at the end
        backindex = 0;  
        elements[backindex] = newElement;
        elementCount++;
    }
    else { // if the array is not full and backindex is not at the end
        backindex++;
        elements[backindex] = newElement;
        elementCount++;
    }
    //cout << "element Count: " << elementCount << endl;
}

// Description: Removes the frontmost element
// Precondition: Queue not empty
// Time Efficiency: O(1)
// void Queue::dequeue() {
//     elementCount--;
//     frontindex = (frontindex + 1) % capacity;
//     return;
// } 



void Queue::dequeue(){

    
    // Check if the array is less than 1/4 full
    if (elementCount < capacity / 4 && capacity > INITIAL_CAPACITY) {

        // // cout << "dequeue " << elements[frontindex] << endl;
        // // elements[frontindex] = 0;
        // // frontindex++;

        // // Halve the capacity (unless it would go below INITIAL_CAPACITY)
        // unsigned int newCapacity;

        // if (capacity / 2 < INITIAL_CAPACITY) {
        //     newCapacity = INITIAL_CAPACITY;
        // } 
        // else {
        //     newCapacity = capacity / 2;
        // }

        // int* newElements = new int[newCapacity];

        // // Copy elements to the new array
        // for (unsigned int i = 0; i < capacity; i++) {
        //     newElements[i] = elements[(frontindex + i) ];
        // }

        // delete[] elements;
        // elements = newElements;
        // frontindex = 0;
        // backindex = elementCount;
        // capacity = newCapacity;



        // using same method using copy constructor and assignment operator
        unsigned int newCapacity;

        if (capacity / 2 < INITIAL_CAPACITY) {
            newCapacity = INITIAL_CAPACITY;
        }
        else {
            newCapacity = capacity / 2;
        }
        Queue temp(*this);
        delete[] elements;
        elements = new int[newCapacity];
        for (unsigned int i = 0; i < temp.capacity; i++) {
            elements[i] = temp.elements[(frontindex + i) % temp.capacity ];
        }
        frontindex = 0;
        backindex = elementCount;
        capacity = newCapacity;




    }

    if (elementCount == 0) {
        return;
    }
    cout << "dequeue " << elements[frontindex] << endl;
    elements[frontindex] = 0;
    
    cout << "after dequeue: " ;
    for (unsigned int i = 0; i < capacity; i++) {
        
        cout << elements[i] << " ";
    }
    cout << endl;



    if(frontindex == backindex) { // if there is only one element in the array
        
        frontindex = 0;
        backindex = 0;
        elementCount--;
    }
    else if (frontindex == capacity-1) { // if frontindex is at the end
        frontindex = 0;
        elementCount--;
    }
    else {
        frontindex++;
        elementCount--;
    }
    
    // Decrease elementCount after dequeue
    // elementCount--;
    //cout << endl << " element Count: " << elementCount << endl;

    // // Check if the array is less than 1/4 full
    // if (elementCount < capacity / 4 && capacity > INITIAL_CAPACITY) {
    //     // Halve the capacity (unless it would go below INITIAL_CAPACITY)
    //     unsigned int newCapacity;

    //     if (capacity / 2 < INITIAL_CAPACITY) {
    //         newCapacity = INITIAL_CAPACITY;
    //     } 
    //     else {
    //         newCapacity = capacity / 2;
    //     }

    //     int* newElements = new int[newCapacity];

    //     // Copy elements to the new array
    //     for (unsigned int i = 0; i < elementCount; i++) {
    //         newElements[i] = elements[(frontindex + i) % capacity];
    //     }

    //     delete[] elements;
    //     elements = newElements;
    //     frontindex = 0;
    //     backindex = elementCount;
    //     capacity = newCapacity;
    //}

    
}


// Implementation of printQueue function
void Queue::printQueue() const {
    if (isEmpty()) {
        cout << "Queue is empty." << endl;
        return;
    }

    // Print elements from front to back
    cout << "Queue elements: ";
    unsigned int index = frontindex;
    for (unsigned int i = 0; i < capacity; i++) {
        cout << elements[i] << " ";
        // index = (index + 1) % capacity;
    }
    cout << endl;
}


// Implementation of getFrontIndex function
unsigned int Queue::getFrontIndex() const {
    return frontindex;
}

// Implementation of getBackIndex function
unsigned int Queue::getBackIndex() const {
    return backindex;
}








// Description: Returns a copy of the frontmost element
// Precondition: Queue not empty
// Time Efficiency: O(1)
int Queue::peek() const {
    return elements[frontindex];    
} 

// Description: Returns true if and only if Queue empty
// Time Efficiency: O(1)
bool Queue::isEmpty() const {
    // cout << "element count: " << elementCount << endl;
    return elementCount == 0;
}

// unsigned int Queue::getElementCount() const {
//     return elementCount;
// }

unsigned int Queue::getElementCount() const{
    return elementCount;
}  

//cout << "element Count: " << elementCount << endl;

// Description: Destructor
Queue::~Queue() {
    delete[] elements;
}