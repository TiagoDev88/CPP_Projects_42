#pragma once

#include <cstdlib>
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

    T& operator[](unsigned int num);
    const T& operator[](unsigned int num) const;
    unsigned int size() const;
};


#include "../src/Array.tpp"