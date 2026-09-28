#include "../inc/RPN.hpp"



RPN::RPN() {}

RPN::RPN(const RPN& other) : _elements(other._elements) { }

RPN& RPN::operator=(const RPN& other)
{
    if (this != &other)
        _elements = other._elements;
    return *this;
}

RPN::~RPN() {}

void RPN::calculateExpression(const std::string& input)
{
    
}