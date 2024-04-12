#pragma once
#include <cmath>
#include <iostream>
#include <stdexcept>

#define DEFAULT_HEAP_SIZE 1023

template <class T>
class MinHeap {
private:
    T* heapArray;
    int size;

    void swap(T& a, T& b) {
        T temp = a;
        a = b;
        b = temp;
    }

    void bubbleUp(int index) {
        int parent = (index - 1) / 2;
        while (index > 0 && heapArray[index] < heapArray[parent]) {
            swap(heapArray[index], heapArray[parent]);
            index = parent;
            parent = (index - 1) / 2;
        }
    }

    void bubbleDown(int index) {
        int leftChild = 2 * index + 1;
        int rightChild = 2 * index + 2;
        int smallest = index;

        if (leftChild < size && heapArray[leftChild] < heapArray[smallest]) {
            smallest = leftChild;
        }
        if (rightChild < size && heapArray[rightChild] < heapArray[smallest]) {
            smallest = rightChild;
        }

        if (smallest != index) {
            swap(heapArray[index], heapArray[smallest]);
            bubbleDown(smallest);
        }
    }

public:
    MinHeap() {
        heapArray = new T[DEFAULT_HEAP_SIZE];
        size = 0;
    }

    int getSize() const {
        return size;
    }

    bool isEmpty() const {
        return size == 0;
    }

    void insert(const T& item) {
        if (size == DEFAULT_HEAP_SIZE) {
            throw std::out_of_range("Heap is full");
        }
        heapArray[size] = item;
        bubbleUp(size);
        size++;
    }

    T extractMin() {
        if (isEmpty()) {
            throw std::out_of_range("Heap is empty");
        }
        T minItem = heapArray[0];
        heapArray[0] = heapArray[size - 1];
        size--;
        bubbleDown(0);
        return minItem;
    }

    T peekMin() const {
        if (isEmpty()) {
            throw std::out_of_range("Heap is empty");
        }
        return heapArray[0];
    }

    ~MinHeap() {
        delete[] heapArray;
    }
};
