#pragma once

#include "arraysequence.h"

template<class T>
ArraySequence<T>::ArraySequence(): _array(new DynamicArray <T>()) {}

template<class T>
ArraySequence<T>::ArraySequence(T* data, int count) {
    _array = new DynamicArray<T>(data, count);
}

template<class T>
ArraySequence<T>::ArraySequence(ArraySequence<T> &array) {
    _array = new DynamicArray<T>(array.GetLength());
    for (int i = 0; i < _array->GetLength(); ++i) {
        _array->Set(array.Get(i), i);
    }
}

template<class T>
T &ArraySequence<T>::GetFirst() {
    try {
        if (_array->GetLength() <= 0)
            throw "Length is an invalid value!";
        return _array->Get(0);
    }  catch (const char *error) {
        std::cout << error << std::endl;
    }
}

template<class T>
T &ArraySequence<T>::GetLast() {
    try {
        if (_array->GetLength() <= 0)
            throw "Length is an invalid value!";
        return _array->Get(this->GetLength() - 1);
    }  catch (const char *error) {
        std::cout << error << std::endl;
    }
}

template<class T>
T &ArraySequence<T>::Get(int index) {
    try {
        if (index < 0 || index >= _array->GetLength())
            throw "Index is out of range!";
        return _array->Get(index);
    }  catch (const char *error) {
        std::cout << error << std::endl;
    }
}

template<class T>
T &ArraySequence<T>::operator[](const int index) {
    try {
        if (index < 0 || index >= _array->GetLength())
            throw "Index is out of range!";
        return this->Get(index);
    }  catch (const char *error) {
        std::cout << error << std::endl;
    }
}

template<class T>
Sequence<T> *ArraySequence<T>::GetSubSequence(int start_index, int end_index) const {
    try {
        if (start_index > end_index || start_index < 0 || end_index < 0 || start_index >= this->GetLength()
                || end_index > this->GetLength())
            throw "Invalid index!";
        Sequence<T> *array = (Sequence<T> *) new DynamicArray<T>(end_index - start_index);
        for (int i = start_index; i < end_index; ++i)
            array->Set(_array->Get(i), i - start_index);
        return array;
    }  catch (const char *error) {
        std::cout << error << std::endl;
    }

}

template<class T>
int ArraySequence<T>::GetLength() const {
    return _array->GetLength();
}

template<class T>
void ArraySequence<T>::DelByIndex(int index) {
    try {
        if (index < 0 || index >= _array->GetLength())
            throw "Index is out of range!";
        _array->DelByIndex(index);
    }  catch (const char *error) {
        std::cout << error << std::endl;
    }
}

template<class T>
void ArraySequence<T>::Prepend(const T &value){
    _array->Resize(this->GetLength()+1);
    for (int i = this->GetLength() - 1; i > 0; --i)
        _array->Set(this->Get(i - 1), i);
    _array->Set(value, 0);
}

template<class T>
void ArraySequence<T>::Append(const T &value) {
    _array->Resize(this->GetLength()+1);
    _array->Set(value, this->GetLength() - 1);
}

template<class T>
void ArraySequence<T>::InsertAt(const T &value, int index) {
    if (index == this->GetLength()) {
        this->Append(value);
        return;
    }
    if (index > this->GetLength()) {
        _array->Resize(index);
        this->Append(value);
        return;
    }
    _array->Resize(this->GetLength() + 1);
    for (int i = this->GetLength() - 1; i > index; --i)
        _array->Set(this->Get(i - 1), i);
    _array->Set(value, index);
}

template<class T>
void ArraySequence<T>::Set(const T &value, int index) {
    if (index >= this->GetLength())
        _array->Resize(index + 1);
    _array->Set(value, index);
}

template<class T>
Sequence<T> *ArraySequence<T>::Concat(Sequence<T> *seq) const {
    try {
        if (seq == nullptr)
            throw "There is no sequence to contact!";
        Sequence<T> *array = (Sequence<T> *) new DynamicArray<T>(_array->GetLength() + seq->GetLength());
        for (int i = 0; i < -array->GetLength(); ++i)
            array->Append(_array->Get(i));
        for (int i = 0; i < seq->GetLength(); ++i)
            array->Append(seq->Get(i));
        return array;
    }  catch (const char *error) {
        std::cout << error << std::endl;
    }
}

template<class T>
void ArraySequence<T>::Swap(T &item_1, T &item_2) {
    T tmp = item_2;
    item_2 = item_1;
    item_1 = tmp;
}

template<class T>
ArraySequence<T>::~ArraySequence() {
    _array->~DynamicArray<T>();
    delete _array;
}
