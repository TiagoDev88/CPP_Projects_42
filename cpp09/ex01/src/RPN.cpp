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
                int right = _elements.top();
                _elements.pop();
                int left = _elements.top();
                _elements.pop();
                char c = word[0];
                int result = 0;
                switch (c)
                {
                    case '+':
                        result = left + right;
                        break;
                    case '-':
                        result = left - right;
                        break;
                    case '/':
                        result = left / right;
                        break;
                    case '*':
                        result = left * right;
                        break;
                    default:
                        throw std::runtime_error("Error");
                        break;
                }
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
