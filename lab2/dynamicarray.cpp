#pragma once

#include <iostream>
#include "dynamicarray.h"

template<class T>
DynamicArray<T>::DynamicArray() {
    _data = nullptr;
    _length = 0;
}

template<class T>
DynamicArray<T>::DynamicArray(T *data, int index) {
    _length = index;
    if(index)
        _data = new T[index];
    else _data = nullptr;
    for (int i = 0; i < _length; i++)
        _data[i] = data[i];
}

template<class T>
DynamicArray<T>::DynamicArray (int length) {
    _length = length;
    if (length != 0)
        _data = new T[length];
    else
        _data = nullptr;
}

template<class T>
DynamicArray<T>::DynamicArray (const DynamicArray<T> &array) {
    _length = array->_length;
    if (_length != 0)
        _data = new T[_length];
    else
        _data = nullptr;
    for (int i = 0; i < _length; i++)
        _data[i] = array->_data[i];
}

template<class T>
T &DynamicArray<T>::Get(int index) {
    try {
        if (index < 0 || index >= _length)
            throw "Index is out of range!";
        return _data[index];
    }  catch (const char *error) {
        std::cout << error << std::endl;
    }
    return _data[0];
}

template<class T>
T &DynamicArray<T>::Get(int index, const T &error) {
    try {
        if (index < 0 || index >= _length)
            throw "Index is out of range!";
        return _data[index];
    }  catch (const char *error) {
        std::cout << error << std::endl;
    }
    return error;
}

template<class T>
void DynamicArray<T>::DelByIndex(int index) {
    try {
        if (index >= _length || index < 0)
            throw "Index is out of range!";
        for (int i = 0; i < _length - 1; ++i) {
            if (i < index) continue;
            else _data[i] = _data[i + 1];
        }
        this->Resize(_length - 1);
    }  catch (const char *error) {
        std::cout << error << std::endl;
    }
}

template<class T>
int DynamicArray<T>::GetLength() const {
    return _length;
}

template<class T>
void DynamicArray<T>::Set(const T &value, int index) {
    try {
        if (index < 0 || index >= _length)
            throw "Index is out of range!";
        _data[index] = value;
    }  catch (const char* error) {
        std::cout << error << std::endl;
    }
}

template<class T>
void DynamicArray<T>::Resize(int length) {
    try {
        if (length < 0)
            throw "Length cannot be negative number!";
        if (!length) {
            delete[] _data;
            _data = nullptr;
            _length = 0;
            return;
        }
        T *array = new T [length];
        for (int i = 0; i < std::min(length, _length); ++i) {
            array[i] = this->Get(i);
        }
        delete[] _data;
        _data = array;
        _length = length;
    }  catch (const char* error) {
        std::cout << error << std::endl;
    }
}

template<class T>
DynamicArray<T>::~DynamicArray() {
    _length = 0;
    delete[] _data;
}
