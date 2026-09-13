#pragma once

#include <cstddef>
#include <iostream>

template<typename T>
class Array
{
    private:
    T* _arr;
    unsigned int _size;

    public:
    Array();
    Array(unsigned int n);
    Array(const Array<T>& other);
    Array<T>& operator=(const Array<T>& other);
    ~Array();
};


#include "../src/Array.tpp"