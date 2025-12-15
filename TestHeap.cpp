#include "Heap.h"
#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <algorithm>
#include <random>

TEST(HeapTest, BasicMinHeap) {
    Heap<int, 10> heap;
    
    EXPECT_TRUE(heap.empty());
    EXPECT_EQ(heap.size(), 0);
    EXPECT_FALSE(heap.full());
    
    heap.insert(5);
    heap.insert(3);
    heap.insert(8);
    heap.insert(1);
    heap.insert(4);
    
    EXPECT_FALSE(heap.empty());
    EXPECT_EQ(heap.size(), 5);
    EXPECT_FALSE(heap.full());
    EXPECT_TRUE(heap.isMin());
    EXPECT_TRUE(heap.isValid());
    
    EXPECT_EQ(heap.top(), 1);
}

TEST(HeapTest, BasicMaxHeap) {
    Heap<int, 10> heap(false);
    
    heap.insert(5);
    heap.insert(3);
    heap.insert(8);
    heap.insert(1);
    heap.insert(4);
    
    EXPECT_TRUE(heap.isValid());
    EXPECT_EQ(heap.top(), 8);
    EXPECT_FALSE(heap.isMin());
}

TEST(HeapTest, ExtractMinHeap) {
    Heap<int, 10> heap;
    std::vector<int> values = {7, 2, 9, 1, 5, 3, 8};
    
    for (int val : values) {
        heap.insert(val);
    }
    
    std::sort(values.begin(), values.end());
    
    for (int expected : values) {
        EXPECT_EQ(heap.top(), expected);
        EXPECT_EQ(heap.extract(), expected);
    }
    
    EXPECT_TRUE(heap.empty());
}

TEST(HeapTest, ExtractMaxHeap) {
    Heap<int, 10> heap(false);
    std::vector<int> values = {7, 2, 9, 1, 5, 3, 8};
    
    for (int val : values) {
        heap.insert(val);
    }
    
    std::sort(values.rbegin(), values.rend());
    
    for (int expected : values) {
        EXPECT_EQ(heap.top(), expected);
        EXPECT_EQ(heap.extract(), expected);
    }
    
    EXPECT_TRUE(heap.empty());
}

TEST(HeapTest, OverflowException) {
    Heap<int, 3> heap;
    
    heap.insert(1);
    heap.insert(2);
    heap.insert(3);
    
    EXPECT_TRUE(heap.full());
    
    EXPECT_THROW({
        heap.insert(4);
    }, std::overflow_error);
}

TEST(HeapTest, UnderflowException) {
    Heap<int, 10> heap;
    
    EXPECT_THROW({
        heap.top();
    }, std::underflow_error);
    
    EXPECT_THROW({
        heap.extract();
    }, std::underflow_error);
    
    EXPECT_THROW({
        heap.remove();
    }, std::underflow_error);
}

TEST(HeapTest, StringMinHeap) {
    Heap<std::string, 10> heap;
    
    heap.insert("banana");
    heap.insert("apple");
    heap.insert("cherry");
    heap.insert("date");
    heap.insert("fig");
    
    EXPECT_TRUE(heap.isValid());
    EXPECT_EQ(heap.top(), "apple");
    
    std::vector<std::string> extracted;
    while (!heap.empty()) {
        extracted.push_back(heap.extract());
    }
    
    for (size_t i = 1; i < extracted.size(); ++i) {
        EXPECT_FALSE(extracted[i] < extracted[i-1]);
    }
}

TEST(HeapTest, StringMaxHeap) {
    Heap<std::string, 10> heap(false);
    
    heap.insert("banana");
    heap.insert("apple");
    heap.insert("cherry");
    heap.insert("date");
    heap.insert("fig");
    
    EXPECT_EQ(heap.top(), "fig");
}

TEST(HeapTest, CopyAndAssignment) {
    Heap<int, 10> heap1;
    heap1.insert(5);
    heap1.insert(2);
    heap1.insert(8);
    
    Heap<int, 10> heap2(heap1);
    EXPECT_EQ(heap1.size(), heap2.size());
    EXPECT_EQ(heap1.top(), heap2.top());
    
    Heap<int, 10> heap3;
    heap3 = heap1;
    EXPECT_EQ(heap1.size(), heap3.size());
    EXPECT_EQ(heap1.top(), heap3.top());
}

TEST(HeapTest, ClearHeap) {
    Heap<int, 10> heap;
    
    heap.insert(1);
    heap.insert(2);
    heap.insert(3);
    
    EXPECT_FALSE(heap.empty());
    heap.clear();
    EXPECT_TRUE(heap.empty());
    EXPECT_EQ(heap.size(), 0);
}

TEST(HeapTest, HeapPropertyAfterOperations) {
    Heap<int, 20> heap;
    std::vector<int> values;
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 100);
    
    for (int i = 0; i < 15; ++i) {
        int val = dis(gen);
        values.push_back(val);
        heap.insert(val);
    }
    
    EXPECT_TRUE(heap.isValid());
    
    for (int i = 0; i < 5; ++i) {
        heap.extract();
        EXPECT_TRUE(heap.isValid());
    }
    
    for (int i = 0; i < 5; ++i) {
        int val = dis(gen);
        heap.insert(val);
        EXPECT_TRUE(heap.isValid());
    }
}

struct Point {
    int x, y;
    
    bool operator<(const Point& other) const {
        return (x*x + y*y) < (other.x*other.x + other.y*other.y);
    }
};

TEST(HeapTest, CustomType) {
    Heap<Point, 10> heap;
    
    heap.insert({3, 4});
    heap.insert({1, 1});
    heap.insert({5, 0});
    heap.insert({0, 0});
    
    EXPECT_EQ(heap.top().x, 0);
    EXPECT_EQ(heap.top().y, 0);
    
    heap.extract();
    EXPECT_EQ(heap.top().x, 1);
    EXPECT_EQ(heap.top().y, 1);
}

TEST(HeapTest, ArrayConstructor) {
    int arr[] = {9, 5, 7, 1, 3, 2};
    Heap<int, 10> heap(arr, 6);
    
    EXPECT_EQ(heap.size(), 6);
    EXPECT_EQ(heap.top(), 1);
    EXPECT_TRUE(heap.isValid());
}

TEST(HeapTest, Iterators) {
    Heap<int, 10> heap;
    heap.insert(3);
    heap.insert(1);
    heap.insert(2);
    
    std::vector<int> values;
    for (auto it = heap.begin(); it != heap.end(); ++it) {
        values.push_back(*it);
    }
    
    EXPECT_EQ(values.size(), 3);
    EXPECT_EQ(values[0], 1);
}

TEST(HeapTest, IndexAccess) {
    Heap<int, 10> heap;
    heap.insert(5);
    heap.insert(3);
    heap.insert(8);
    
    EXPECT_EQ(heap[0], 3);
    EXPECT_EQ(heap.size(), 3);
    
    EXPECT_THROW({
        heap[10];
    }, std::out_of_range);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
