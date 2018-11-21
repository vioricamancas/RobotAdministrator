// Copyright 2018

#ifndef DOUBLYLINKEDLIST_H_
#define DOUBLYLINKEDLIST_H_

#include <assert.h>
#include <iostream>

template <typename T>
struct Node {
    T data;
    Node<T> *next;
    Node<T> *prev;

    explicit Node(T data) {
        this->data = data;
        next = NULL;
        prev = NULL;
    }
};

template <typename T>
class DoublyLinkedList {
 private:
        Node<T> *head;
        Node<T> *tail;
        int numElements;

        /**
         * Returns the pos'th node in the list.
         */
        Node<T> *goToPos(int pos) {
            int count = 0;
            Node<T> *temp = head;
            while (count != pos) {
                temp = temp->next;
                count++;
            }
            return temp;
        }

 public:
        // Constructor
        DoublyLinkedList() {
            head = NULL;
            tail = NULL;
            numElements = 0;
        }

        // Another constructor
       explicit DoublyLinkedList(Node<T> *head) {
            this->head = head;
            while (head != NULL) {
                numElements++;
                head = head->next;
            }
        }

        // Destructor
        ~DoublyLinkedList() {
            while (tail != NULL){
                Node<T> *n = tail;
                tail = tail->prev;
                delete n;
            }
            delete tail;
        }

        /**
         * Adds a new node at the end of the list.
         */
        void addLast(T data) {
            Node<T> *newElem = new Node<T>(data);
            if (numElements == 0) {
                head = newElem;
                tail = newElem;
            } else {
                tail->next = newElem;
                newElem->prev = tail;
            }
            tail = newElem;
            numElements++;
        }

        /**
         * Adds a new node at the beginning of the list.
         */
        void addFirst(T data) {
            Node<T> *newElem = new Node<T>(data);
            newElem->prev = NULL;
            newElem->next = head;
            numElements++;
            if (head == NULL) {
                head = tail = newElem;
            } else {
                head->prev = newElem;
                head = newElem;
            }
        }

        /**
         * Removes the last node of the list.
         */
        T removeLast() {
            if (numElements > 0){
            T aux = tail->data;
                Node<T> *n = tail;
                tail = tail->prev;
                delete n;
                if (tail != NULL)
                    tail->next = NULL;
            numElements--;
            if (numElements == 0) {
                    delete tail;
                    head = tail;
            }
            return aux;
        }
        return T();
        }

        /**
         * Removes the first node of the list.
         */
        T removeFirst() {
            T aux = head->data;
            if (numElements > 1) {
                Node<T> *n = head;
                head =  head->next;
                head->prev = NULL;
                delete n;
            }
            numElements--;
            if (!numElements) {
                    delete head;
                    tail = head = NULL;
            }
            return aux;
        }

        /**
         * Check if the list contains any elements.
         */
        bool isEmpty() {
            if (numElements == 0)
                return true;
            return false;
        }

        /**
         * Returns the number of nodes in the list.
         */
        int size() {
            return numElements;
        }

        /**
         * Adds a new node on the specified position in the list.
         */
        void addOnPos(T element, int pos) {
            if (pos < numElements && pos >= 0){
                numElements++;
                Node<T> *newElem = new Node<T>(element);
                Node<T>* aux = goToPos(pos);
                newElem->prev = aux->prev;
                aux->prev->next = newElem;
                aux->prev = newElem;
                newElem->next = aux;
            } else {
                std::cout << "Invalid";
            }
        }

        /**
         * Removes the node on the specified position and returns the value it stored.
         */
        T removeFromPos(int pos) {
            if (pos < numElements && pos >= 0){
                if (pos == 0) {
                    removeFirst();
                } else {
                    if (pos == numElements-1) {
                        removeLast();
                    } else {
                        Node<T>* aux;
                        aux = goToPos(pos);
                        T c = aux->data;
                        aux->next->prev = aux->prev;
                        aux->prev->next = aux->next;
                        numElements--;
                        return c;
                    }
                }
            } else {
                std::cout << "Invalid";
            }
            T c = 0;
            return c;
        }

        // Getters & Setters
        Node<T> *getHead() {
            return head;
        }

        Node<T> *getTail() {
            return tail;
        }

        template <typename U>
        friend std::ostream& operator<<(std::ostream& os,
                DoublyLinkedList<U>& list);
};

template <typename T>
std::ostream& operator<<(std::ostream& os, DoublyLinkedList<T>& list) {
    Node<T> *it = list.getHead();

    if (list.size() > 0) {
        os << "[ ";
        while (it->next != NULL) {
            os << it->data << " <-> ";
            it = it->next;
        }

        os << it->data;
        os << " ]";
    } else {
        os << "[]";
    }

    return os;
}

#endif  // DOUBLYLINKEDLIST_H_
