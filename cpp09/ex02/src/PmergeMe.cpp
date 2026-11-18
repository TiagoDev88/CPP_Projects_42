#include "PmergeMe.hpp"
#include <algorithm>
#include <cctype>
#include <climits>
#include <stdexcept>

PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe& other)
: _vec(other._vec), _input(other._input), _deq(other._deq) {}

PmergeMe& PmergeMe::operator=(const PmergeMe& other)
{
    if (this != &other)
    {
        _vec = other._vec;
        _input = other._input;
        _deq = other._deq;
    }
    return *this;
}

PmergeMe::~PmergeMe() {}

// Returns the order in which the "low" elements are inserted into the main chain.
// The values are indexes of the low vector, ready to use: low[order[0]], low[order[1]], ...
// low[0] is not included because it always goes first, with no comparisons.
// Ex.: total = 5  ->  2 1 4 3
std::vector<std::size_t> PmergeMe::jacobsthalNumbers(std::size_t total)
{
    std::vector<std::size_t> order;

    std::size_t done = 1;     // how many low elements are already handled (low[0])
    std::size_t prev = 1;     // previous Jacobsthal number
    std::size_t jump = 3;     // current Jacobsthal number: 3, 5, 11, 21, ...

    while (done < total)
    {
        std::size_t top = std::min(jump, total);

        // walk backwards from top until the ones already done
        for (std::size_t i = top; i > done; i--)
            order.push_back(i - 1);   // -1 because the low vector starts at 0

        done = top;

        std::size_t next = jump + 2 * prev;
        prev = jump;
        jump = next;
    }
    return order;
}

int PmergeMe::parseNumber(const std::string& str)
{
    if (str.empty())
        throw std::invalid_argument("empty argument");
    for (std::size_t i = 0; i < str.size(); i++)
    {
        if (!std::isdigit(static_cast<unsigned char>(str[i])))
            throw std::invalid_argument("not a positive integer: " + str);
    }

    long value;
    std::stringstream ss(str);
    ss >> value;
    if (ss.fail() || value > INT_MAX || value == 0)
        throw std::out_of_range("out of range: " + str);
    return static_cast<int>(value);
}

void PmergeMe::run(int argc, char** argv)
{
    for (int i = 1; i < argc; i++)
    {
        _input.push_back(parseNumber(argv[i]));
        std::cout << argv[i] << " ,";
    }
    _vec = sortVector(_input);
    
    std::cout << std::endl;

    for (size_t i = 0; i < _vec.size(); i++)
    {
        std::cout << "vector " << _vec[i] << ", " << std::endl;
    }
    
}

// Merge-Insertion Sort ==  Ford-Johnson

std::vector<int> PmergeMe::sortVector(std::vector<int> vec)
{
    if (vec.size() < 2)
        return vec;

    bool isOdd = (vec.size() % 2 != 0);
    std::vector<int> leftover;
    if (isOdd)
    {
        std::cout << "odd size\n";
        leftover.push_back(vec.back());
        vec.pop_back();
    }
    std::vector<std::pair<int, int> > pair;
    for(size_t i = 0; i < vec.size(); i+=2)
    {
        if (vec[i] > vec[i + 1])
        {
            pair.push_back(std::make_pair(vec[i], vec[i + 1]));
        }
        else
        {
            pair.push_back(std::make_pair(vec[i + 1], vec[i]));
        }
    }
    
    std::vector<int> high;

    for (size_t i = 0; i < pair.size(); i++)
        high.push_back(pair[i].first);
    
    high = sortVector(high);

    // used[j] stops the same pair from being picked twice when there are repeated "a" values
    std::vector<int> low;
    std::vector<bool> used(pair.size(), false);
    for (size_t i = 0; i < high.size(); i++)
    {
        for (size_t j = 0; j < pair.size(); j++)
        {
            if (!used[j] && pair[j].first == high[i])
            {
                low.push_back(pair[j].second);
                used[j] = true;
                break;
            }
        }
    }
    std::cout << std::endl;

    if (isOdd)
        low.push_back(leftover[0]);
    std::vector<int> mainChain(high);
    mainChain.insert(mainChain.begin(), low[0]);

    std::vector<std::size_t> order = jacobsthalNumbers(low.size());
    for (std::size_t i = 0; i < order.size(); i++)
    {
        std::size_t pos = order[i];
        int value = low[pos];

        // low[pos] is smaller than its pair high[pos], so we only search before it.
        // The leftover has no pair, so it searches the whole chain.
        std::vector<int>::iterator limit = mainChain.end();
        if (pos < high.size())
            limit = std::find(mainChain.begin(), mainChain.end(), high[pos]);

        std::vector<int>::iterator where = std::lower_bound(mainChain.begin(), limit, value);
        mainChain.insert(where, value);
    }
    return mainChain;
}

// TODO: implement Ford-Johnson for deque
std::deque<int> PmergeMe::sortDeque(std::deque<int> deq)
{
    return deq;
}