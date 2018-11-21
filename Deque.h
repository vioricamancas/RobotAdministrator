/**
 * Deque.h
Copyright 2018
 */

#ifndef DEQUE_H_
#define DEQUE_H_

#include <assert.h>
#include "DoublyLinkedList.h"

template <typename T>
class Deque {
 private:
    DoublyLinkedList<T> data;

 public:
    // Constructor
    Deque() {
    }

    // Destructor
    ~Deque() {
    }

    /**
     * Add a new element at the back of the deque.
     * 
     * @param element Value of the element to be added in the deque.
     */
    void push_back(T element) {
        data.addLast(element);
    }

    /**
     * Add a new element at the front of the deque.
     * 
     * @param element Value of the element to be added in the deque.
     */
    void push_front(T element) {
        data.addFirst(element);
    }

    /**
     * Removes and returns an element from the back of the deque.
     *
     * @return Value of the elmement removed from the deque.
     */
    T pop_back() {
        return data.removeLast();
    }

    /**
     * Removes and returns an element from the back of the deque.
     *
     * @return Value of the elmement removed from the deque.
     */
    T pop_front() {
        return data.removeFirst();
    }

    /**
     * Returns an element from the front of the deque, without removing it.
     *
     * @return Value of the first element stored in the deque (deque front).
     */
    T front() {
        return data.getHead()->data;
    }

    /**
     * Returns an element from the front of the deque, without removing it.
     *
     * @return Value of the first element stored in the deque (deque front).
     */
    T back(){
        return data.getTail()->data;
    }

    /**
     * Checks if the deque contains any elements.
     *
     * @return True if the deque contains no elements, False otherwise.
     */
    bool isEmpty() {
        return data.isEmpty();
    }

    /**
     * Returns the number of elements currently stored in the deque.
     *
     * @return The number of elements stored in the deque.
     */
    int size() {
        return data.size();
    }

    template <typename U, int M>
    friend std::ostream& operator<<(std::ostream& os, Deque<U>& deque);
};

template <typename T>
std::ostream& operator<<(std::ostream& os, Deque<T>& deque) {
    os << "Front to rear: ";
    T *aux = new T[deque.size()];
    int i = 0;
    while (!deque.isEmpty()) {
        aux[i] = deque.pop_front();
        os << aux[i++] << " ";
    }
    for (int j = 0; j < i-1; j++)
        deque.push_back(aux[j]);
    delete[] aux;
    return os;
}

#endif  // DEQUE_H_
