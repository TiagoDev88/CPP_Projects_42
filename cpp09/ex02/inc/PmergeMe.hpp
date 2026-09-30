#pragma once

#include <vector>
#include <deque>

class PmergeMe
{
    private:
    std::vector<int> _vec;
    std::deque<int> _deq;
    void fordJohnsonAlgorithm();
    std::vector<int> sortVector(std::vector<int>& vec);
    std::deque<int> sortDeque(std::deque<int>& deq);

    public:
    PmergeMe();
    PmergeMe(const PmergeMe& other);
    PmergeMe& operator=(const PmergeMe& other);
    ~PmergeMe();

    void sortAndDisplay();
};