#include "../inc/PmergeMe.hpp"

PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe& other) 
: _vec(other._vec), _deq(other._deq) {}

PmergeMe& PmergeMe::operator=(const PmergeMe& other)
{
    if (this != &other)
    {
        _vec = other._vec;
        _deq = other._deq;
    }
    return *this;
}

PmergeMe::~PmergeMe() {}

static void jacobsthalNumbers(std::size_t number)
{

}

void PmergeMe::run()
{

}

// Merge-Insertion Sort ==  Ford-Johnson

std::vector<int> PmergeMe::sortVector(std::vector<int>& vec)
{

}

std::deque<int> PmergeMe::sortDeque(std::deque<int>& deq)
{
    
}