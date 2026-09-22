#include <algorithm>
#include <stack>
#include <iostream>

template<typename T>
class MutantStack : public std::stack<T>
{
    private:

    public:
    MutantStack<T>();
    MutantStack<T>(const MutantStack<T>& other);
    MutantStack<T>& operator=(const MutantStack<T>& other);
    ~MutantStack<T>();

    typedef typename std::stack<T>::container_type::iterator iterator;
    typedef typename std::stack<T>::container_type::const_iterator const_iterator;

    iterator begin();
    iterator end();

    const_iterator begin() const;
    const_iterator end() const;

};

#include "../src/MutantStack.tpp"