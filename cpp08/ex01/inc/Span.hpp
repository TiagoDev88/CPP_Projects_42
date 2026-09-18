#pragma once


#include <vector>
#include <iostream>
#include <exception>
#include <algorithm>


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
        
    }
};