#include "../inc/Span.hpp"

Span::Span() : _capacity(0), _storage() {}

Span::Span(unsigned int capacity) : _capacity(capacity), _storage() {}

Span::Span(const Span& other) :
 _capacity(other._capacity), _storage(other._storage)  {}

Span& Span::operator=(const Span& other)
{
    if (this != &other)
    {
        _capacity = other._capacity;
        _storage = other._storage;
    }
    return *this;
}

Span::~Span() {}

void Span::addNumber(int n)
{
    if (_storage.size() < _capacity)
        _storage.push_back(n);
    else
        throw std::out_of_range("Error: Span is full!");
}

unsigned int Span::shortestSpan() const
{
    if (_storage.size() < 2)
        throw std::logic_error("Error: Not enough numbers, please add min two numbers.");

    std::vector<int> tmp = _storage;
    std::sort(tmp.begin(), tmp.end());
    unsigned int minDistance = static_cast<unsigned int>(static_cast<long long>(tmp[1]) - tmp[0]);

    for(unsigned int i = 1; i < tmp.size() - 1; ++i)
    {
        unsigned int distanceNextNumber = static_cast<unsigned int>(static_cast<long long>(tmp[i + 1]) - tmp[i]);
        if (distanceNextNumber < minDistance)
            minDistance = distanceNextNumber; 
    }
    return minDistance;
}

unsigned int Span::longestSpan() const
{
    if (_storage.size() < 2)
        throw std::logic_error("Error: Not enough numbers, please add min two numbers.");

    std::vector<int> tmp = _storage;
    std::sort(tmp.begin(), tmp.end());

    return static_cast<unsigned int>(static_cast<long long>(tmp.back()) - tmp.front());
}
