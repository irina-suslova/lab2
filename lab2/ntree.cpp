#pragma once

#include "ntree.h"
#include <fstream>
#include <arraysequence.cpp>

template<class T>
NTree<T>::NTree() {
    _size = 1;
    _root = new TreeItem<T>();
}

template<class T>
NTree<T>::NTree(T &data) {
    _size = 1;
    _root = new TreeItem<T>(data);
}

template<class T>
void NTree<T>::SetItem(TreeItem<T> *item, T &data) {
    item->_data = data;
}

template<class T>
int NTree<T>::GetSize() {
    return _size;
}

template<class T>
void NTree<T>::Add(TreeItem<T> *parent, T &data) {
    TreeItem<T> *item = new TreeItem<T>(data, parent);
    parent->_chilgren->Append(item);
    ++_size;
}

template<class T>
TreeItem<T> *NTree<T>::GetRoot() {
    return _root;
}

template<class T>
Sequence<TreeItem<T> *> *NTree<T>::GetChildrenOf(TreeItem<T> *item) {
    return item->_chilgren;
}

template<class T>
TreeItem<T> *NTree<T>::GetParentrenOf(TreeItem<T> *item) {
    return item->_parent;
}

template<class T>
Sequence<T> *NTree<T>::GetSequenceChildrenOf(TreeItem<T> *item)  {
    Sequence<T> *Children = new ArraySequence<T>;
    for (int i = 0; i < item->_chilgren->GetLength(); ++i)
        Children->Append(((*item->_chilgren)[i])->_data);
    return Children;
}

template<class T>
Sequence<T> *NTree<T>::GetSequenceChildrenOf(TreeItem<T> *item, Sequence<T> *children) {
    for (int i = 0; i < item->_chilgren->GetLength(); ++i)
        children->Append((*item->_chilgren)[i]);
    return children;
}

template<class T>
T &NTree<T>::GetTParentrenOf(TreeItem<T> *item) {
    return item->_parent->_data;
}

template<class T>
Sequence<TreeItem<T>*> *NTree<T>::GetAllLeaves(TreeItem<T>* root) {
    Sequence<TreeItem<T>*> *leaves = new ArraySequence<TreeItem<T>*>;

    TreeItem<T>* it = root;

    Sequence<int> *indexes = new ArraySequence<int>;
    indexes->Append(0);

    if (it->_chilgren->GetLength() == 0) {
        leaves->Append(it);
        return leaves;
    }

    while(root->_chilgren->GetLength() != (*indexes)[0]) {
        if (it->_chilgren->GetLength() == 0) {
            leaves->Append(it);
            it = it->_parent;
            indexes->DelByIndex(indexes->GetLength() - 1);
            indexes->GetLast() += 1;
            continue;
        }
        if (indexes->GetLast() >= it->_chilgren->GetLength()) {
            it = it->_parent;
            indexes->DelByIndex(indexes->GetLength() - 1);
            indexes->GetLast() += 1;
            continue;
        }
        it = (*it->_chilgren)[indexes->GetLast()];
        indexes->Append(0);
    }
    return leaves;
}

template<class T>
Sequence<T> *NTree<T>::GetSequenceAllLeaves(TreeItem<T>* root) {
    Sequence<T> *leaves = new ArraySequence<T>;

    TreeItem<T>* it = root;

    Sequence<int> *indexes = new ArraySequence<int>;
    indexes->Append(0);

    if (it->_chilgren->GetLength() == 0) {
        leaves->Append(it->_data);
        return leaves;
    }

    while(root->_chilgren->GetLength() != (*indexes)[0]) {
        if (it->_chilgren->GetLength() == 0) {
            leaves->Append(it->_data);
            it = it->_parent;
            indexes->DelByIndex(indexes->GetLength() - 1);
            indexes->GetLast() += 1;
            continue;
        }
        if (indexes->GetLast() >= it->_chilgren->GetLength()) {
            it = it->_parent;
            indexes->DelByIndex(indexes->GetLength() - 1);
            indexes->GetLast() += 1;
            continue;
        }
        it = (*it->_chilgren)[indexes->GetLast()];
        indexes->Append(0);
    }
    return leaves;
}

template<class T>
Sequence<TreeItem<T> *> *NTree<T>::GetLeavesByCondition(TreeItem<T> *root, bool (*condition)(T)) {
    Sequence<TreeItem<T>*> *leaves = new ArraySequence<TreeItem<T>*>;

    TreeItem<T>* it = root;

    Sequence<int> *indexes = new ArraySequence<int>;
    indexes->Append(0);

    if (it->_chilgren->GetLength() == 0) {
        if (condition(it->_data)) leaves->Append(it);
        return leaves;
    }

    while(root->_chilgren->GetLength() != (*indexes)[0]) {
        if (it->_chilgren->GetLength() == 0) {
            if (condition(it->_data))
                leaves->Append(it);
            it = it->_parent;
            indexes->DelByIndex(indexes->GetLength() - 1);
            indexes->GetLast() += 1;
            continue;
        }
        if (indexes->GetLast() >= it->_chilgren->GetLength()) {
            it = it->_parent;
            indexes->DelByIndex(indexes->GetLength() - 1);
            indexes->GetLast() += 1;
            continue;
        }
        it = (*it->_chilgren)[indexes->GetLast()];
        indexes->Append(0);
    }

    return leaves;
}

template<class T>
Sequence<T> *NTree<T>::GetSequenceLeavesByCondition(TreeItem<T>* root, bool (*condition)(T)) {
    Sequence<T> *leaves = new ArraySequence<T>;

    TreeItem<T>* it = root;

    Sequence<int> *indexes = new ArraySequence<int>;
    indexes->Append(0);

    if (it->_chilgren->GetLength() == 0) {
        if (condition(it->_data)) leaves->Append(it->_data);
        return leaves;
    }

    while(root->_chilgren->GetLength() != (*indexes)[0]) {
        if (it->_chilgren->GetLength() == 0) {
            if (condition(it->_data)) leaves->Append(it->_data);
            it = it->_parent;
            indexes->DelByIndex(indexes->GetLength() - 1);
            indexes->GetLast() += 1;
            continue;
        }
        if (indexes->GetLast() >= it->_chilgren->GetLength()) {
            it = it->_parent;
            indexes->DelByIndex(indexes->GetLength() - 1);
            indexes->GetLast() += 1;
            continue;
        }
        it = (*it->_chilgren)[indexes->GetLast()];
        indexes->Append(0);
    }

    return leaves;
}

template<class T>
int NTree<T>::CountAllLeaves(TreeItem<T> *root) {
    int n;

    TreeItem<T>* it = root;

    Sequence<int> *indexes = new ArraySequence<int>;
    indexes->Append(0);

    if (it->_chilgren->GetLength() == 0) {
        n = 1;
        return n;
    }

    while(root->_chilgren->GetLength() != (*indexes)[0]) {
        if (it->_chilgren->GetLength() == 0) {
            ++n;
            it = it->_parent;
            indexes->DelByIndex(indexes->GetLength() - 1);
            indexes->GetLast() += 1;
            continue;
        }
        if (indexes->GetLast() >= it->_chilgren->GetLength()) {
            it = it->_parent;
            indexes->DelByIndex(indexes->GetLength() - 1);
            indexes->GetLast() += 1;
            continue;
        }
        it = (*it->_chilgren)[indexes->GetLast()];
        indexes->Append(0);
    }
    return n;
}

template<class T>
int NTree<T>::CountLeavesByCondition(TreeItem<T> *root, bool (*condition)(T)) {
    int n = 0;

    TreeItem<T>* it = root;

    Sequence<int> *indexes = new ArraySequence<int>;
    indexes->Append(0);

    if (it->_chilgren->GetLength() == 0) {
        if (condition(it->_data)) ++n;
        return n;
    }

    while(root->_chilgren->GetLength() != (*indexes)[0]) {
        if (it->_chilgren->GetLength() == 0) {
            if (condition(it->_data))
                ++n;
            it = it->_parent;
            indexes->DelByIndex(indexes->GetLength() - 1);
            indexes->GetLast() += 1;
            continue;
        }
        if (indexes->GetLast() >= it->_chilgren->GetLength()) {
            it = it->_parent;
            indexes->DelByIndex(indexes->GetLength() - 1);
            indexes->GetLast() += 1;
            continue;
        }
        it = (*it->_chilgren)[indexes->GetLast()];
        indexes->Append(0);
    }

    return n;
}
