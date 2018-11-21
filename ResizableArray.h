// Copyright 2018

#ifndef RESIZABLEARRAY_H_
#define RESIZABLEARRAY_H_

#include <assert.h>
#include <typeinfo>
template <typename T>
class ResizableArray {
 private:
        int defaultCapacity = 5;
        int expandFactor = 2;

        int numElements;
        int maxCapacity;
        T *data;

 public:
        // Constructor
        ResizableArray() {
            numElements = 0;
            maxCapacity = defaultCapacity;
            data = new T[maxCapacity];
        }

        // Copy onstuctor

        ResizableArray(const ResizableArray& other) {
            numElements = other.numElements;
            maxCapacity = other.maxCapacity;
            data = new T[maxCapacity];
            for (int i = 0; i < numElements; i++)
                data[i] = other.data[i];
        }

        // Another constructor
        explicit ResizableArray(int initialCapacity) {
            numElements = 0;
            maxCapacity = initialCapacity;
            data = new T[maxCapacity];
        }

        // Another constructor
        ResizableArray(int initialCapacity, int defaultFactor) {
            numElements = 0;
            maxCapacity = initialCapacity;
            expandFactor = defaultFactor;
            data = new T[maxCapacity];
        }

        // Destructor
        ~ResizableArray() {
            delete[] data;
        }

#define e(i, j) std::get<j>(i)  // gets elem on pos j of tuple named i

        /**
         * Adds the specified element at the end of the array.
         */
        void addLast(T element) {
            if (numElements == maxCapacity) {
                maxCapacity *= expandFactor;
                T* newdata = new T[maxCapacity];
                for (int i = 0; i < numElements; i++)
                    newdata[i] = data[i];
                delete[] data;
                data = newdata;
            }
            data[numElements] = element;
            numElements++;
        }

        /**
         * Adds the specified element at the beginning of the array.
         */
        void addFirst(T element) {
            data[0] = element;
            numElements++;
}
        /**
         * Adds the specified element on pos'th position of the array.
         */
        void addOnPos(T element, int pos) {
            if (numElements+1 > maxCapacity) {
                maxCapacity *= expandFactor;
                T* newdata = new T[maxCapacity];
                for (int i = 0; i < pos; i++)
                    newdata[i] = data[i];
                for (int i = pos; i < numElements; i++)
                    newdata[i+1] = data[i];
                delete[] data;
                data = newdata;
            } else {
                for (int i = numElements-1; i >= pos; i--)
                    data[i+1] = data[i];
            }
            data[pos] = element;
            numElements++;
        }

        /**
         * Removes and returns the last element of the array.
         */

        T removeLast() {
            T c = data[numElements-1];
            if (numElements <= maxCapacity / 2) {
                maxCapacity /= 2;
            }
            T* newdata = new T[maxCapacity];
            for (int i = 0; i < numElements; i++)
                newdata[i] = data[i];
            delete[] data;
            data = newdata;
            numElements--;
            return c;
        }

        /**
         * Removes and returns the first element of the array.
         */
        T removeFirst() {
            T c = data[0];
            if (numElements > 0){
            T* newdata = new T[numElements-1];
                for (int i = 1; i < numElements; i++)
                    newdata[i-1] = data[i];
                delete[] data;
            data = newdata;
            numElements--;}
            return c;
        }

        /**
         * Removes and returns the pos'th element of the array.
         */
        T removeFromPos(int pos) {
            T c = data[pos];
            T* newdata = new T[numElements-1];
                for (int i = 0; i < numElements; i++){
                    if (i == pos)
                        continue;
                    if (i > pos)
                        newdata[i-1] = data[i];
                    else
                        newdata[i] = data[i];
                }
                delete[] data;
            data = newdata;
            numElements--;
            return c;
        }

        /**
         * Returns the number of elements in the array.
         */
        int size() const {
            return numElements;
        }

        /**
         * Checks if the array contains any elements.
         */
        bool isEmpty() {
            if (numElements == 0)
                return true;
            else
                return false;
        }

        // Getters & Setters
        T *getData() const {
            return data;
        }

        T getLast() {
            return data[numElements-1];
        }
        int getCapacity() {
            return maxCapacity;
        }

        template <typename U>
        friend std::ostream& operator<<(std::ostream& os,
                const ResizableArray<U>& ra);
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const ResizableArray<T>& ra) {
    os << "[ ";
    for (int i = 0; i < ra.size(); i++) {
        os << (ra.getData())[i] << " ";
    }
    os << "]";

    return os;
}

#endif  // RESIZABLEARRAY_H_
