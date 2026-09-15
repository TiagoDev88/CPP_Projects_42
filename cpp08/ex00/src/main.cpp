#include "../inc/easyfind.hpp"

#include <vector>
#include <iostream>
#include <list>

int main()
{
    std::cout << "----Testing with Vector----" << std::endl;
    std::vector<int> vec;

    for(int i = 0; i < 10; i++)
        vec.push_back(i * 5);

    try
    {
        std::vector<int>::iterator it = ::easyfind(vec, 40);
        std::cout << "Find in the vector: " << *it << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

        try
    {
        std::vector<int>::iterator it = ::easyfind(vec, 42);
        std::cout << "Find in the vector: " << *it << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    std::cout << "\n----Testing with List----" << std::endl;
    
    std::list<int> lst;

    for(int i = 0; i < 10; i++)
        lst.push_back(i * 3);
        
    try
    {
        std::list<int>::iterator it = ::easyfind(lst, 18);
        std::cout << "Find in the list: " << *it << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

        try
    {
        std::list<int>::iterator it = ::easyfind(lst, 42);
        std::cout << "Find in the vector: " << *it << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    return 0;
}