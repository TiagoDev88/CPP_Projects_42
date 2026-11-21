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

static bool isOperator(char &c)
{
    return (c == '+' || c == '-' || c == '/' || c == '*');
}

void RPN::calculateExpression(const std::string& input)
{
    std::istringstream inp(input);
    std::string word;

    while(inp >> word)
    {
        if (word.length() == 1 && std::isdigit(static_cast<unsigned char>(word[0])))
            this->_elements.push(word[0] - '0');
        else if (word.length() == 1 && isOperator(word[0]))
        {
            if (_elements.size() > 1)
            {
                long right = _elements.top();
                _elements.pop();
                long left = _elements.top();
                _elements.pop();
                char c = word[0];
                long result = 0;
                switch (c)
                {
                    case '+':
                        result = left + right;
                        break;
                    case '-':
                        result = left - right;
                        break;
                    case '/':
                        if (right == 0)
                            throw std::runtime_error("Error");
                        if (left == INT_MIN && right == -1)
                            throw std::runtime_error("Error");
                        result = left / right;
                        break;
                    case '*':
                        result = left * right;
                        break;
                    default:
                        throw std::runtime_error("Error");
                        break;
                }
                if (result < INT_MIN || result > INT_MAX)
                    throw std::runtime_error("Error");
                _elements.push(result);
            }
            else
                throw std::runtime_error("Error");
        }
        else
            throw std::runtime_error("Error");
    }
    if (_elements.size() != 1)
        throw std::runtime_error("Error");
    std::cout << _elements.top() << std::endl;
}
