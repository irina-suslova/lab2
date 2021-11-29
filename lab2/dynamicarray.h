#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H

#pragma once

template<class T>
class DynamicArray {

private:
    T *_data;
    int _length;

public:
    //Constructors
    DynamicArray();
    DynamicArray(T *data, int index);
    DynamicArray(int length);
    DynamicArray(const DynamicArray<T>& array);

    //Decomposition
    T& Get(int index);
    T& Get(int index, const T &error);
    void DelByIndex(int index);
    int GetLength() const;

    //Operations
    void Set(const T &value, int index);
    void Resize(int length);

    //Destructor
    ~DynamicArray();
};

#endif // DYNAMICARRAY_H
