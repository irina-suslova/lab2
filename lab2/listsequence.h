#ifndef LISTSEQUENCE_H
#define LISTSEQUENCE_H

#pragma once

#include "sequence.h"
#include "linkedlist.h"
#include "linkedlist.cpp"
#include "iostream"

template <class T>
class ListSequence: public Sequence<T> {

private:
    LinkedList<T> *_list;

public:
    //Constructors
    ListSequence();
    ListSequence(T* data, int count);
    ListSequence(const ListSequence<T>& list);

    //Decomposition
    T& GetFirst();
    T& GetLast();
    T& Get(int index);
    T& operator[] (const int index);
    Sequence<T> *GetSubSequence(int start_index, int end_index) const;
    int GetLength() const;
    void DelByIndex(int index);

    //Operations
    void Append(const T& value);
    void Prepend(const T& value);
    void InsertAt(const T& value, int index);
    void Set(const T& item, int index);
    Sequence<T> *Concat(Sequence<T> *seq) const;
    void Swap(T& item_1, T& item_2);

    //Destructor
    ~ListSequence();
};

#endif // LISTSEQUENCE_H
