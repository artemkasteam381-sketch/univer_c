#ifndef HEAP_H
#define HEAP_H

#include <stdexcept>
#include <algorithm>

template <typename T, size_t Capacity>
class Heap {
private:
    T data[Capacity];
    size_t currentSize;
    bool isMinHeap;
    
    size_t parent(size_t idx) const { return (idx - 1) / 2; }
    size_t leftChild(size_t idx) const { return 2 * idx + 1; }
    size_t rightChild(size_t idx) const { return 2 * idx + 2; }
    
    void siftUp(size_t idx) {
        if (idx == 0) return;
        
        size_t p = parent(idx);
        if (isMinHeap) {
            while (idx > 0 && data[idx] < data[p]) {
                std::swap(data[idx], data[p]);
                idx = p;
                p = parent(idx);
            }
        } else {
            while (idx > 0 && data[p] < data[idx]) {
                std::swap(data[idx], data[p]);
                idx = p;
                p = parent(idx);
            }
        }
    }
    
    void siftDown(size_t idx) {
        while (leftChild(idx) < currentSize) {
            size_t child = leftChild(idx);
            
            if (isMinHeap) {
                if (child + 1 < currentSize && data[child + 1] < data[child]) {
                    child++;
                }
                if (data[child] < data[idx]) {
                    std::swap(data[idx], data[child]);
                    idx = child;
                } else {
                    break;
                }
            } else {
                if (child + 1 < currentSize && data[child] < data[child + 1]) {
                    child++;
                }
                if (data[idx] < data[child]) {
                    std::swap(data[idx], data[child]);
                    idx = child;
                } else {
                    break;
                }
            }
        }
    }

public:
    Heap(bool minHeap = true) : currentSize(0), isMinHeap(minHeap) {}
    
    Heap(const T* arr, size_t n, bool minHeap = true) : currentSize(0), isMinHeap(minHeap) {
        for (size_t i = 0; i < n && i < Capacity; ++i) {
            insert(arr[i]);
        }
    }
    
    Heap(const Heap& other) : currentSize(other.currentSize), isMinHeap(other.isMinHeap) {
        for (size_t i = 0; i < currentSize; ++i) {
            data[i] = other.data[i];
        }
    }
    
    Heap& operator=(const Heap& other) {
        if (this != &other) {
            currentSize = other.currentSize;
            isMinHeap = other.isMinHeap;
            for (size_t i = 0; i < currentSize; ++i) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }
    
    void insert(const T& value) {
        if (currentSize >= Capacity) {
            throw std::overflow_error("Куча заполнена!");
        }
        
        data[currentSize] = value;
        siftUp(currentSize);
        currentSize++;
    }
    
    T top() const {
        if (currentSize == 0) {
            throw std::underflow_error("Куча пуста!");
        }
        return data[0];
    }
    
    void remove() {
        if (currentSize == 0) {
            throw std::underflow_error("Куча пуста!");
        }
        
        data[0] = data[currentSize - 1];
        currentSize--;
        if (currentSize > 0) {
            siftDown(0);
        }
    }
    
    T extract() {
        if (currentSize == 0) {
            throw std::underflow_error("Куча пуста!");
        }
        
        T root = data[0];
        remove();
        return root;
    }
    
    bool empty() const {
        return currentSize == 0;
    }
    
    bool full() const {
        return currentSize == Capacity;
    }
    
    size_t size() const {
        return currentSize;
    }
    
    size_t capacity() const {
        return Capacity;
    }
    
    bool isMin() const {
        return isMinHeap;
    }
    
    void clear() {
        currentSize = 0;
    }
    
    bool isValid() const {
        for (size_t i = 1; i < currentSize; ++i) {
            size_t p = parent(i);
            if (isMinHeap) {
                if (data[i] < data[p]) return false;
            } else {
                if (data[p] < data[i]) return false;
            }
        }
        return true;
    }
    
    const T& operator[](size_t idx) const {
        if (idx >= currentSize) {
            throw std::out_of_range("Индекс вне границ кучи");
        }
        return data[idx];
    }
    
    const T* begin() const { return data; }
    const T* end() const { return data + currentSize; }
};

#endif
