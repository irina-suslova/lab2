#ifndef NTREE_H
#define NTREE_H

#pragma once

#include <iostream>
#include <sequence.h>
#include <fstream>
#include <string.h>
#include <arraysequence.cpp>
using namespace std;



template <class T>
class TreeItem {
public:
    T _data;
    TreeItem *_parent;
    Sequence<TreeItem<T>*> *_chilgren;
    TreeItem(T data = T(), TreeItem *parent = nullptr, Sequence<TreeItem*> *chilgren = nullptr) {
        this->_data = data;
        this->_parent = parent;
        if (!chilgren) {
            _chilgren = new ArraySequence<TreeItem<T>*>;
        }
        else this->_chilgren = chilgren;
    }
};

template <class T>
class NTree {
    TreeItem<T> *_root;
    int _size;
public:
    NTree();
    NTree(T &data);

    void SetItem(TreeItem<T>* item, T& data);

    int GetSize();
    void Add(TreeItem<T>* parent, T &data);

    TreeItem<T> *GetRoot();

    Sequence<TreeItem<T>*> *GetChildrenOf(TreeItem<T>* item);
    Sequence<T> *GetSequenceChildrenOf(TreeItem<T> *item);
    Sequence<T> *GetSequenceChildrenOf(TreeItem<T>* item,  Sequence<T> *children);

    TreeItem<T> *GetParentrenOf(TreeItem<T>* item);
    T& GetTParentrenOf(TreeItem<T>* item);

    Sequence<TreeItem<T>*> *GetAllLeaves(TreeItem<T>* root);
    Sequence<T> *GetSequenceAllLeaves(TreeItem<T>* root);
    Sequence<TreeItem<T>*> *GetLeavesByCondition(TreeItem<T>* root, bool (*condition)(T));
    Sequence<T> *GetSequenceLeavesByCondition(TreeItem<T>* root, bool (*condition)(T));
    int CountAllLeaves(TreeItem<T>* root);
    int CountLeavesByCondition(TreeItem<T> *root, bool (*condition)(T));

    ~NTree();
};

#endif // NTREE_H
