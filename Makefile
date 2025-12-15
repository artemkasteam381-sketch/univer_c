CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g -I.

all: test example

sparsevector.o: SparseVector.cpp SparseVector.h
	$(CXX) $(CXXFLAGS) -c SparseVector.cpp -o sparsevector.o

test_sparsevector: TestSparseVector.cpp sparsevector.o
	$(CXX) $(CXXFLAGS) TestSparseVector.cpp sparsevector.o -lgtest -lgtest_main -lpthread -o test_sparsevector

test: test_sparsevector
	./test_sparsevector

example.o: example.cpp SparseVector.h
	$(CXX) $(CXXFLAGS) -c example.cpp -o example.o

example_program: example.o sparsevector.o
	$(CXX) $(CXXFLAGS) example.o sparsevector.o -o example_program

example: example_program
	./example_program

simple_test: TestSimple.cpp SparseVector.cpp
	$(CXX) $(CXXFLAGS) TestSimple.cpp SparseVector.cpp -o simple_test
	./simple_test

clean:
	rm -f *.o test_sparsevector example_program simple_test

.PHONY: all test example clean simple_test
