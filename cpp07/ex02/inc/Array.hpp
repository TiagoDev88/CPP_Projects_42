#pragma once

#include <cstddef>
#include <iostream>

template<typename T>
class Array
{
    private:
    T arr;

    public:
    Array();
    Array(T value);
    Array(const Array& other);
    Array& operator=(const Array& other);
    ~Array();
    T getArr() const;
};


#include "../src/Array.tpp"