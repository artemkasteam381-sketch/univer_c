#ifndef HEAP_H
#define HEAP_H

#include <stdexcept>

template <typename T, size_t Capacity>
class Heap {
private:
    T data[Capacity];
    size_t currentSize;
    bool isMinHeap;
    
    size_t parent(size_t idx) const;
    size_t leftChild(size_t idx) const;
    size_t rightChild(size_t idx) const;
    
    void siftUp(size_t idx);
    void siftDown(size_t idx);

public:
    Heap(bool minHeap = true);
    Heap(const T* arr, size_t n, bool minHeap = true);
    Heap(const Heap& other);
    Heap& operator=(const Heap& other);
    
    void insert(const T& value);
    T top() const;
    void remove();
    T extract();
    
    bool empty() const;
    bool full() const;
    size_t size() const;
    size_t capacity() const;
    bool isMin() const;
    void clear();
    bool isValid() const;
    
    const T& operator[](size_t idx) const;
    const T* begin() const;
    const T* end() const;
};

#include "Heap.tpp"

#endif
