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
    //fazer aqui uma verificacao
    // da quantidade de numeros que ja guardei
    //antes de guardar, caso nao tenha espaco,
    //lanco excecao
    if (_storage.size() < _capacity)
        _storage.push_back(n);
    else
        throw std::range_error("Error: Span is full!");
}

unsigned int Span::shortestSpan() const
{
    if (_storage.size() < 2)
        throw std::logic_error("Error: Not enough numbers, please add min two numbers.");

    std::vector<int> tmp = _storage;
    std::sort(tmp.begin(), tmp.end(), std::less<int>());
    unsigned int minDistance = tmp[1] - tmp[0];

    for(unsigned int i = 1; i < tmp.size() - 1; ++i)
    {
        unsigned int distanceNextNumber = tmp[i + 1] - tmp[i];
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
    std::sort(tmp.begin(), tmp.end(), std::greater<int>());
    
    unsigned int maxDistance = 0;

    for(unsigned int i = 1; i < tmp.size(); ++i)
    {
        unsigned int distanceNextNumber = tmp[0] - tmp[i];
        if (distanceNextNumber > maxDistance)
            maxDistance = distanceNextNumber; 
    }
    return maxDistance;
}

// como o longestSpan, e sempre a diferenca entre o primeiro elemento
// e o segundo elemento, basta subtrair o ultimo pelo primeiro e tenho a distancia.
// nao preciso de fazer o for, porque ja sei os valores ordenados
// uso o tmp.front() e o tmp.back() -> para ir buscar o valor em vez do ponteiro.
