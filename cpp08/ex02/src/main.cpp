#include "../inc/MutantStack.hpp"
#include <list>


int main()
{
    MutantStack<int> mstack;
    std::list<int> li;
    mstack.push(5);
    li.push_back(5);
    mstack.push(17);
    li.push_back(17);
    std::cout << mstack.top() << std::endl;
    std::cout << li.back() << std::endl;
    mstack.pop();
    li.pop_back();
    std::cout << mstack.size() << std::endl;
    std::cout << li.size() << std::endl;
    mstack.push(3);
    li.push_back(3);

    mstack.push(5);
    li.push_back(5);

    mstack.push(737);
    li.push_back(737);

    mstack.push(0);
    li.push_back(0);

    MutantStack<int>::iterator it = mstack.begin();
    std::list<int>::iterator itl = li.begin();
    MutantStack<int>::iterator ite = mstack.end();
    std::list<int>::iterator itle = li.end();

    ++it;
    ++itl;
    --it;
    --itl;

    std::cout << std::endl;
    std::cout << std::endl;
    while (it != ite)
    {
    std::cout << *it << std::endl;
    ++it;
    }
    std::cout << std::endl;
    std::cout << std::endl;

    while(itl != itle)
    {
        std::cout << *itl << std::endl;
        ++itl;
    }
    std::stack<int> s(mstack);
    return 0;
}