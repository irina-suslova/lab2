#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#pragma once

template <class T>
class LinkedList {
private:
    class Node {
    public:
        T data;
        Node *pNext;
        Node(T data = T(), Node *pNext = nullptr) {
            this->data = data;
            this->pNext = pNext;
        }
    };
    Node *_head;
    int _length;

public:
    //Constructors
    LinkedList();
    LinkedList(T* data, int count);
    LinkedList(const LinkedList <T>& list);


    //Decomposition
    T& Front() const;
    T& Back() const;
    T& Get(int index) const;
    void PopFront();
    void PopBack();
    void DelByIndex(int index);
    void Clear();
    LinkedList<T>* GetSubList(int start_index, int end_index) const;
    int GetLength() const;

    //Operations
    void PushFront(const T& data);
    void PushBack(const T& data);
    void InsertAt(const T& data, int index);
    void Set(const T& data, int index);
    LinkedList<T>* Concat(LinkedList<T> *list) const;


    //Destructor
    ~LinkedList();
};

#endif // LINKEDLIST_H
