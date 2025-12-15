#ifndef HEAP_TPP
#define HEAP_TPP

#include <algorithm>

template <typename T, size_t Capacity>
size_t Heap<T, Capacity>::parent(size_t idx) const { 
    return (idx - 1) / 2;
}

template <typename T, size_t Capacity>
size_t Heap<T, Capacity>::leftChild(size_t idx) const { 
    return 2 * idx + 1;
}

template <typename T, size_t Capacity>
size_t Heap<T, Capacity>::rightChild(size_t idx) const { 
    return 2 * idx + 2;
}

// Восстановление свойств кучи снизу вверх
template <typename T, size_t Capacity>
void Heap<T, Capacity>::siftUp(size_t idx) {
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

// Восстановление свойств кучи сверху вниз
template <typename T, size_t Capacity>
void Heap<T, Capacity>::siftDown(size_t idx) {
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

// Конструкторы
template <typename T, size_t Capacity>
Heap<T, Capacity>::Heap(bool minHeap) 
    : currentSize(0), isMinHeap(minHeap) {}

template <typename T, size_t Capacity>
Heap<T, Capacity>::Heap(const T* arr, size_t n, bool minHeap) 
    : currentSize(0), isMinHeap(minHeap) {
    for (size_t i = 0; i < n && i < Capacity; ++i) {
        insert(arr[i]);
    }
}

// Конструктор копирования
template <typename T, size_t Capacity>
Heap<T, Capacity>::Heap(const Heap& other) 
    : currentSize(other.currentSize), isMinHeap(other.isMinHeap) {
    for (size_t i = 0; i < currentSize; ++i) {
        data[i] = other.data[i];
    }
}

// Оператор присваивания
template <typename T, size_t Capacity>
Heap<T, Capacity>& Heap<T, Capacity>::operator=(const Heap& other) {
    if (this != &other) {
        currentSize = other.currentSize;
        isMinHeap = other.isMinHeap;
        for (size_t i = 0; i < currentSize; ++i) {
            data[i] = other.data[i];
        }
    }
    return *this;
}

// Основные операции
template <typename T, size_t Capacity>
void Heap<T, Capacity>::insert(const T& value) {
    if (currentSize >= Capacity) {
        throw std::overflow_error("Куча заполнена!");
    }
    
    data[currentSize] = value;
    siftUp(currentSize);
    currentSize++;
}

template <typename T, size_t Capacity>
T Heap<T, Capacity>::top() const {
    if (currentSize == 0) {
        throw std::underflow_error("Куча пуста!");
    }
    return data[0];
}

template <typename T, size_t Capacity>
void Heap<T, Capacity>::remove() {
    if (currentSize == 0) {
        throw std::underflow_error("Куча пуста!");
    }
    
    data[0] = data[currentSize - 1];
    currentSize--;
    if (currentSize > 0) {
        siftDown(0);
    }
}

template <typename T, size_t Capacity>
T Heap<T, Capacity>::extract() {
    if (currentSize == 0) {
        throw std::underflow_error("Куча пуста!");
    }
    
    T root = data[0];
    remove();
    return root;
}

// Состояние кучи
template <typename T, size_t Capacity>
bool Heap<T, Capacity>::empty() const {
    return currentSize == 0;
}

template <typename T, size_t Capacity>
bool Heap<T, Capacity>::full() const {
    return currentSize == Capacity;
}

template <typename T, size_t Capacity>
size_t Heap<T, Capacity>::size() const {
    return currentSize;
}

template <typename T, size_t Capacity>
size_t Heap<T, Capacity>::capacity() const {
    return Capacity;
}

template <typename T, size_t Capacity>
bool Heap<T, Capacity>::isMin() const {
    return isMinHeap;
}

template <typename T, size_t Capacity>
void Heap<T, Capacity>::clear() {
    currentSize = 0;
}

// Проверка корректности структуры
template <typename T, size_t Capacity>
bool Heap<T, Capacity>::isValid() const {
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

// Доступ по индексу
template <typename T, size_t Capacity>
const T& Heap<T, Capacity>::operator[](size_t idx) const {
    if (idx >= currentSize) {
        throw std::out_of_range("Индекс вне границ кучи");
    }
    return data[idx];
}

// Итераторы
template <typename T, size_t Capacity>
const T* Heap<T, Capacity>::begin() const { 
    return data;
}

template <typename T, size_t Capacity>
const T* Heap<T, Capacity>::end() const { 
    return data + currentSize;
}

#endif
