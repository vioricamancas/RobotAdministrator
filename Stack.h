// Copyright 2018
#ifndef STACK_H_
#define STACK_H_

#include <assert.h>
#include "ResizableArray.h"
#include <vector>

/**
 * First template parameter is the datatype of the elements to be stored.
 * Second template parameter is the maximum stack size.
 */
template <typename T>
class Stack {
 private:
    // Underlying array
    ResizableArray<T> data;
    int topLevel;

 public:
    // Constructor
    Stack() {
        topLevel = 0;
    }

    // Destructor
    ~Stack() {
        // while (!data.isEmpty())
        //     data.removeLast();
    }

    /**
     * Adds an element on top of the stack.
     *
     * @param element Element to be added to the stack.
     */
    void push(T element) {
        topLevel++;
        data.addLast(element);
    }

    /**
     * Removes the top element of the stack.
     */
    T pop() {
        topLevel--;
        return data.removeLast();
    }

    /**
     * Retrieves the top value stored in the stack.
     *
     * @return Value of the element stored on top of the stack.
     */
    T peek() {
        return data.getLast();
    }

    /**
     * Checks if the stack contains any elements.
     *
     * @return True if the stack contains no elements, False otherwise.
     */
    bool isEmpty() {
        if (!topLevel)
            return true;
        return false;
    }

    /**
     * Returns the number of elements currently stored in the stack.
     *
     * @return The number of elements stored in the stack.
     */
    int size() {
        return topLevel;
    }

    int getCapacity() {
        return data.getCapacity();
    }

    template <typename U>
    friend std::ostream& operator<<(std::ostream& os, Stack<U>& stack);
};

#define e(i, j) std::get<j>(i)  // gets elem on pos j of tuple named i

template <typename T>
std::ostream& operator<<(std::ostream& os, Stack<T>& stack) {
    os << "Bottom to top: ";
    T *aux = new T[stack.size()];
    int i = 0;
    while (!stack.isEmpty()){
        aux[i++] = stack.peek();
        stack.pop();
    }
    for (int j = i-1; j >= 0; j--){
        os << e(aux[j], 0) << " " << e(e(aux[j], 1), 3);
        stack.push(aux[j]);
    }
    os <<"\n";
    delete[] aux;
    return os;
}

#endif  // STACK_H_
