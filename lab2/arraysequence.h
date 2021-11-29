#ifndef ARRAYSEQUENCE_H
#define ARRAYSEQUENCE_H

#pragma once

#include "sequence.h"
#include "dynamicarray.h"
#include "dynamicarray.cpp"
#include "iostream"

template <class T>
class ArraySequence: public Sequence<T> {

private:
    DynamicArray<T> *_array;

public:
    //Constructors
    ArraySequence();
    ArraySequence(T* data, int count);
    ArraySequence(ArraySequence<T>& array);

    //Decomposition
    T& GetFirst();
    T& GetLast();
    T& Get(int index);
    T& operator[] (const int index);
    Sequence<T>* GetSubSequence(int start_index, int end_index) const;
    int GetLength() const;
    void DelByIndex(int index);

    //Operations
    void Append(const T& value);
    void Prepend(const T& value);
    void InsertAt(const T& value, int index);
    void Set(const T& value, int index);
    Sequence<T>* Concat(Sequence <T> *seq) const;
    void Swap(T& item_1, T& item_2);

    //Destructor
    ~ArraySequence();
};


#endif // ARRAYSEQUENCE_H

