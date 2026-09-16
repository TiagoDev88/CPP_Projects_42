#include "../inc/Span.hpp"

Span::Span() : _storage() {}

Span::Span(unsigned int capacity) : _capacity(capacity)
{
    // _storage.reserve(capacity);
}

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
    //fazer aqui uma verificacao
    // da quantidade de numeros que ja guardei
    //antes de guardar, caso nao tenha espaco,
    //lanco excecao
    if (_storage.size() < _capacity)
        _storage.push_back(n);
    else
        throw std::range_error("Error: Span is full!");
}

int Span::shortestSpan() const
{
    /*
     aqui verificar se tenho so um numero
     porque so um numero nao posso comparar.
     caso tenha so um numero, lanco excecao
    */
    if (_storage.size() < 2)
        throw std::logic_error("Error: Not enough numbers, please add min two numbers.");

    std::vector<int> tmp = _storage;
    std::sort(tmp.begin(), tmp.end());
    unsigned int minDistance = tmp[1] - tmp[0]; // verifica o segundo com o primeiro.

    for(unsigned int i = 1; i < tmp.size() - 1; ++i)
    {
        unsigned int distanceNextNumber = tmp[i + 1] - tmp[i];
        if (distanceNextNumber < minDistance)
            minDistance = distanceNextNumber; 
    }
    return minDistance;
    
}

int Span::longestSpan() const
{
    /*
     aqui verificar se tenho so um numero
     porque so um numero nao posso comparar.
     caso tenha so um numero, lanco excecao
    */
    if (_storage.size() < 2)
        throw std::logic_error("Error: Not enough numbers, please add min two numbers.");

    std::vector<int> tmp = _storage;
    std::sort(tmp.begin(), tmp.end(), std::greater<int>());
    unsigned int minDistance = tmp[0] - tmp[1]; // verifica o segundo com o primeiro.

    for (unsigned int i = tmp.size() - 1; i > 0; i--)
    std::cout << tmp[i] << ", ";
    // for(unsigned int i = 0; i < tmp.size() - 1; ++i)
    // {
    //     int distanceNextNumber = tmp[i + 1] - tmp[i];
    //     if (distanceNextNumber > minDistance)
    //         minDistance = distanceNextNumber; 
    // }
    return minDistance;
}