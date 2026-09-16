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

    public:
    Span();
    Span(unsigned int n);
    Span(const Span& other);
    Span& operator=(const Span& other);
    ~Span();

    void addNumber(int n);
    int shortestSpan() const;
    int longestSpan() const;
};