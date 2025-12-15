CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -I.
GTEST_FLAGS = -lgtest -lgtest_main -lpthread

all: test example

test: TestHeap.cpp Heap.h
	$(CXX) $(CXXFLAGS) TestHeap.cpp $(GTEST_FLAGS) -o heap_test
	./heap_test

example: example.cpp Heap.h
	$(CXX) $(CXXFLAGS) example.cpp -o heap_example
	./heap_example

clean:
	rm -f heap_test heap_example

.PHONY: all test example clean
