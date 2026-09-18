#pragma once


#include <vector>
#include <iostream>
#include <exception>
#include <algorithm>
#include <stdexcept> // for out_of_range and logic_error
#include <iterator> // for std::distance


class Span
{
    private:
    unsigned int _capacity;
    std::vector<int> _storage;
    Span();

    public:
    Span(unsigned int n);
    Span(const Span& other);
    Span& operator=(const Span& other);
    ~Span();

    void addNumber(int n);
    unsigned int shortestSpan() const;
    unsigned int longestSpan() const;

    template<typename T>
    void addMultipleNumbers(T begin, T end)
    {
        unsigned int distance = std::distance(begin, end);
        if(distance > _capacity - _storage.size())
            throw std::out_of_range("Error: Span is full!");
        _storage.insert(_storage.end(), begin, end);
    }
};