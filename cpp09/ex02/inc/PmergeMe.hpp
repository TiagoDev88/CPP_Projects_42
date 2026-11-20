#pragma once

#include <vector>
#include <deque>
#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <ctime>


class PmergeMe
{
    private:
    static int parseNumber(const std::string& str);
    static std::vector<std::size_t> jacobsthalNumbers(std::size_t total);

    template <typename Container>
    static Container sortInput(Container cont);

    public:
    PmergeMe();
    PmergeMe(const PmergeMe& other);
    PmergeMe& operator=(const PmergeMe& other);
    ~PmergeMe();

    void run(int argc, char** argv) const;
};