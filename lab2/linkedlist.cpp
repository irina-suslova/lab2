#pragma once

#include <iostream>
#include "linkedlist.h"


template<class T>
LinkedList<T>::LinkedList() {
    _length = 0;
    _head = nullptr;
}

template<class T>
LinkedList<T>::LinkedList(T *data, int count) : LinkedList() {
    for (int i = 0; i < count; i++)
        PushBack(data[i]);
}

template<class T>
LinkedList<T>::LinkedList(const LinkedList<T> &list) : LinkedList() {
    Node *node = list._head;
    for (int i = 0; i < list._length; i++) {
        PushBack(node->data);
        node = node->pNext;
    }
}

template<class T>
T &LinkedList<T>::Front() const {
    try {
        if (!this->_length)
            throw "The list is empty!";
        T &front = this->_head->data;
        return front;
    }  catch (const char* error) {
        std::cout << error << std::endl;
    }
}

template<class T>
T &LinkedList<T>::Back() const {
    try {
        if (!this->_length)
            throw "The list is empty!";
        Node *node = this->_head;
        for (int i = 0; i < this->_length; ++i) {
            node = node->pNext;
        }
        T &back = node->data;
        return back;
    }  catch (const char* error) {
        std::cout << error << std::endl;
    }
}

template<class T>
T &LinkedList<T>::Get(int index) const {
    try {
        if (index >= this->_length || index < 0)
            throw "Index out of range!";
        Node *node = this->_head;
        for (int i = 0; i < index; ++i) {
            node = node->pNext;
        }
        T &value = node->data;
        return value;
    } catch(const char* error) {
        std::cout << error << std::endl;
    }
}

template<class T>
void LinkedList<T>::PopFront() {
    try {
        if (!this->_length)
            throw "The list is empty!";
        Node* del_node = this->_head;
        this->_head = this->_head->pNext;
        delete del_node;
        --this->_length;
    }  catch (const char* error) {
        std::cout << error << std::endl;
    }
}

template<class T>
void LinkedList<T>::PopBack() {
    try {
        if (!this->_length)
            throw "The list is empty!";
        Node* node = this->_head;
        for (int i = 0; i < this->_length - 1; ++i) node = node->pNext;
        Node* del_node = node->pNext;
        node->pNext = nullptr;
        delete del_node;
        --this->_length;
    }  catch (const char* error) {
        std::cout << error << std::endl;
    }
}

template<class T>
void LinkedList<T>::Clear() {
    while (_length)
        PopFront();
}

template<class T>
void LinkedList<T>::DelByIndex(int index) {
    try {
        if (index < 0 || index >= _length)
            throw "Index is out of range";
        if (!index) {
            Node *n_del = _head;
            _head = _head->pNext;
            delete n_del;
            --_length;
            return;
        }
        Node *n = _head;
        for (int i = 1; i < index; ++i) {
            n = n->pNext;
        }
        Node *n_del = n->pNext;
        n->pNext = n->pNext->pNext;
        delete n_del;
        --_length;
    }  catch (const char *error) {
        std::cout << error << std::endl;
    }
}

template<class T>
LinkedList<T> *LinkedList<T>::GetSubList(int start_index, int end_index) const {
    try {
        if (start_index < 0 || start_index >= this->_length || end_index < 0 || end_index > this->_length)
            throw "Index is out of range!";
        if (start_index > end_index)
            std::swap(start_index, end_index);
        LinkedList<T>* list = new LinkedList<T>;
        for (int i = start_index; i < end_index; ++i)
            (*list).PushBack(this->Get(i));
        return list;
    }  catch (const char* error) {
        std::cout << error << std::endl;
    }
}

template<class T>
int LinkedList<T>::GetLength() const {
    return _length;
}

template<class T>
void LinkedList<T>::PushFront(const T &data) {
    Node* new_node = new Node;
    *new_node = Node(data);
    if (!this->_length) {
        this->_head = new_node;
        ++this->_length;
        return;
    }
    new_node->pNext = this->_head;
    this->_head = new_node;
}

template<class T>
void LinkedList<T>::PushBack(const T &data) {
        Node* new_node = new Node;
        new_node->data = data;
        new_node->pNext = nullptr;
        if (!this->_length) {
            this->_head = new_node;
            ++this->_length;
            return;
        }
        Node *node = this->_head;
        for(int i = 0; i < this->_length - 1; ++i) {
            node = node->pNext;
        }
        node->pNext = new_node;
        ++this->_length;
}

template<class T>
void LinkedList<T>::InsertAt(const T &data, int index) {
    try {
        if (index < 0 || index > this->_length)
            throw "Index is out of range!";
        if (!index) {
            this->PushFront(data);
            return;
        }
        if (index == this->_length) {
            this->PushBack(data);
            return;
        }
        Node* node = this->_head;
        for (int i = 0; i < index - 1; ++i) {
            node = node->pNext;
        }
        Node* new_node = new Node;
        *new_node = Node(data, node->pNext);
        node->pNext = new_node;
        ++this->_length;
    }  catch (const char* error) {
        std::cout << error << std::endl;
    }
}

template<class T>
void LinkedList<T>::Set(const T &data, int index) {
    try {
        if (index < 0 || index > this->_length)
            throw "Index is out of range!";
        if (index == _length) {
            this->PushBack(data);
            return;
        }
        Node* node = this->_head;
        for (int i = 0; i < index; ++i) {
            node = node->pNext;
        }
        node->data = data;
    }  catch (const char* error) {
        std::cout << error << std::endl;
    }
}

template<class T>
LinkedList<T> *LinkedList<T>::Concat(LinkedList<T> *list) const {
    try {
        if (list == nullptr)
            throw "There is no list to contact!";
        LinkedList<T>* new_list = new LinkedList<T>;
        for (int i = 0; i < this->GetLength(); ++i) {
            new_list->PushBack(this->Get(i));
        }
        for (int i = 0; i < list->GetLength(); ++i) {
            new_list->PushBack(list->Get(i));
        }
        return new_list;
    }  catch (const char *error) {
        std::cout << error << std::endl;
    }
}

template<class T>
LinkedList<T>::~LinkedList() {
    Clear();
}
