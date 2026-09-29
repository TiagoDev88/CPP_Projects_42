#pragma once
#include <iostream>
#include <stack>
#include <exception>
#include <sstream>


class RPN
{
    private:
    std::stack<int> _elements;

    public:
    RPN();
    RPN(const RPN& other);
    RPN& operator=(const RPN& other);
    ~RPN();

    void calculateExpression(const std::string& input);
};