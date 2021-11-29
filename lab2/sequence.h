#ifndef SEQUENCE_H
#define SEQUENCE_H

#pragma once

#include "linkedlist.h"
#include "dynamicarray.h"

template<class T>
class Sequence {

public:
    //Decomposition
    virtual T& GetFirst() = 0;
    virtual T& GetLast() = 0;
    virtual T& Get(int index) = 0;
    virtual T& operator[] (const int index) = 0;
    virtual Sequence<T> *GetSubSequence(int start_index, int end_index) const = 0;
    virtual int GetLength() const = 0;
    virtual void DelByIndex(int index) = 0;

    //Operations
    virtual void Append(const T& value) = 0;
    virtual void Prepend(const T& value) = 0;
    virtual void InsertAt(const T& value, int index) = 0;
    virtual void Set(const T& item, int index) = 0;
    virtual Sequence<T> *Concat(Sequence<T> *Sequence) const = 0;
    virtual void Swap(T& item_1, T& item_2) = 0;
};

#endif // SEQUENCE_H
