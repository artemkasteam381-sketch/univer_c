#ifndef SPARSEVECTOR_H
#define SPARSEVECTOR_H

#include <iostream>

class SparseVector{
private:
    class Node
    {
    public:
        int index;
        int value;
        Node *next;
        Node(int index, int value, Node *next = nullptr):
        index(index), value(value), next(next) { }
    };
    Node *head;
    int s;
    void clear();
    void copyList(const SparseVector &sv);
    void SetNonezeroel(int idx, int val);
    void remzerel(int idx);
    void checklistorder();        
    void addSubVector(const SparseVector &sv, bool add);
    void removeZeros();
public:
    SparseVector(int size){
        head = nullptr;
        s = size;
    }
    SparseVector(const SparseVector& other) {
        head = nullptr;
        s = other.s;
        copyList(other);
    }
    ~SparseVector(){
        clear();
    }
    int getSize() const{
        return s;
    }
    void push_back(int index, int value);
    SparseVector& operator=(const SparseVector& other);
    bool operator==(const SparseVector& other) const;
    bool operator!=(const SparseVector& other) const;
    SparseVector& operator+=(const SparseVector& other);
    SparseVector& operator-=(const SparseVector& other);
    SparseVector operator+(const SparseVector &) const;
    SparseVector operator-(const SparseVector &) const;
    int getElem(int idx);
    void setElem(int index, int value);
};

#endif // SPARSEVECTOR_H
