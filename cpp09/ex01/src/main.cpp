#include "../inc/RPN.hpp"


// Reverse Polish Notation - o operador vem depois dos numeros
int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cerr << "Error: please input a inverted Polish mathematical expression as an argument."
                << std::endl;
        return -1;
    }
    try
    {
        RPN rpn;
        std::string input(argv[1]);
        rpn.calculateExpression(input);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    return 0;
}