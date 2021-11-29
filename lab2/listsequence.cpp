#pragma once

#include "listsequence.h"
#include "linkedlist.h"

template<class T>
ListSequence<T>::ListSequence(): _list(new LinkedList <T>()) {}

template<class T>
ListSequence<T>::ListSequence(T *data, int count) {
    _list = new LinkedList<T>(data, count);
}

template<class T>
ListSequence<T>::ListSequence(const ListSequence<T> &list) {
    _list = new LinkedList<T>(*list._list);
}

template<class T>
T &ListSequence<T>::GetFirst() {
    try {
        if (!_list->GetLength())
            throw "The list is empty!";
        return _list->Front();
    }  catch (const char* error) {
        std::cout << error << std::endl;
    }
}

template<class T>
T &ListSequence<T>::GetLast() {
    return Get(_list->GetLength() - 1);
}

template<class T>
T &ListSequence<T>::Get(int index) {
    try {
        if (index >= _list->GetLength() || index < 0)
            throw "Index out of range!";
        return _list->Get(index);
    } catch(const char* error) {
        std::cout << error << std::endl;
    }
}

template<class T>
T &ListSequence<T>::operator[](const int index) {
    try {
        if (index >= _list->GetLength() || index < 0)
            throw "Index out of range!";
        return this->Get(index);
    } catch(const char* error) {
        std::cout << error << std::endl;
    }
}

template<class T>
Sequence<T> *ListSequence<T>::GetSubSequence(int start_index, int end_index) const {
    try {
        if (start_index < 0 || start_index >= _list->GetLength() || end_index < 0 || end_index > _list->GetLength())
            throw "Index is out of range!";
        return (Sequence<T> *) _list->GetSubList(start_index, end_index);
    }  catch (const char* error) {
        std::cout << error << std::endl;
    }
}

template<class T>
int ListSequence<T>::GetLength() const {
    return _list->GetLength();
}

template<class T>
void ListSequence<T>::DelByIndex(int index) {
    try {
        if (index < 0 || index >= this->GetLength())
            throw "Index is out of range";
        _list->DelByIndex(index);
    }  catch (const char *error) {
        std::cout << error << std::endl;
    }
}

template<class T>
void ListSequence<T>::Append(const T &value){
    _list->PushBack(value);
}

template<class T>
void ListSequence<T>::Prepend(const T &value) {
    _list->PushFront(value);
}

template<class T>
void ListSequence<T>::InsertAt(const T &value, int index) {
    try {
        if (index < 0 || index > _list->GetLength())
            throw "Index is out of range!";
        _list->InsertAt(value, index);
    }  catch (const char* error) {
        std::cout << error << std::endl;
    }
}

template<class T>
void ListSequence<T>::Set(const T &value, int index) {
    try {
        if (index < 0 || index > _list->GetLength())
            throw "Index is out of range!";
        _list->Set(value, index);
    }  catch (const char* error) {
        std::cout << error << std::endl;
    }
}

template<class T>
Sequence<T> *ListSequence<T>::Concat(Sequence<T> *seq) const {
    try {
        if (seq == nullptr)
            throw "There is no sequence to contact!";
        ListSequence<T> *seq_list = new ListSequence<T>();
        for (int i = 0; i < seq->GetLength(); ++i) {
            seq_list->Append(seq->Get(i));
        }
        ListSequence<T> *contacted = new ListSequence<T>();
        contacted->_list = _list->Concat(seq_list->_list);
        return (Sequence<T> *) contacted;
    }  catch (const char *error) {
        std::cout << error << std::endl;
    }
}

template<class T>
void ListSequence<T>::Swap(T &item_1, T &item_2) {
    T tmp = item_2;
    item_2 = item_1;
    item_1 = tmp;
}

template<class T>
ListSequence<T>::~ListSequence() {
    _list->~LinkedList<T>();
    delete _list;
}

