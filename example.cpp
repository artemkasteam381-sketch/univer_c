#include "Heap.h"
#include <iostream>

int main() {
    Heap<int, 5> minHeap;
    
    minHeap.insert(5);
    minHeap.insert(3);
    minHeap.insert(8);
    minHeap.insert(1);
    minHeap.insert(4);
    
    std::cout << "Min heap: ";
    while (!minHeap.empty()) {
        std::cout << minHeap.extract() << " ";
    }
    std::cout << std::endl;
    
    Heap<std::string, 4> maxHeap(false);
    
    maxHeap.insert("banana");
    maxHeap.insert("apple");
    maxHeap.insert("cherry");
    maxHeap.insert("date");
    
    std::cout << "Max heap strings: ";
    while (!maxHeap.empty()) {
        std::cout << maxHeap.extract() << " ";
    }
    std::cout << std::endl;
    
    return 0;
}
