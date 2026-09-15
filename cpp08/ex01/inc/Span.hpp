#pragma once


#include <vector>



class Span
{
    private:
    unsigned int _n;
    std::vector<int> _storage;

    public:
    Span();
    Span(unsigned int n);
    Span(const Span& other);
    Span& operator=(const Span& other);
    ~Span();

    void addNumber(int n);
    int shortestSpan();
    int longestSpan();
};