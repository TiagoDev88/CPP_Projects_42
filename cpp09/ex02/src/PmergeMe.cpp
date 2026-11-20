#include "PmergeMe.hpp"
#include <algorithm>
#include <cctype>
#include <climits>
#include <stdexcept>

PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe& other) { (void)other;}

PmergeMe& PmergeMe::operator=(const PmergeMe& other)
{
    (void)other;
    return *this;
}

PmergeMe::~PmergeMe() {}

std::vector<std::size_t> PmergeMe::jacobsthalNumbers(std::size_t sizeLows)
{
    std::vector<std::size_t> insertOrder;
    std::size_t done = 1, prev = 1, current = 3; 

    // 1 loop adds one group to insertOrder
    while (done < sizeLows)
    {
        // current or the last from sizeLows
        std::size_t groupEnd = std::min(current, sizeLows);

        // run the group from end to begin (from that group)
        for (std::size_t i = groupEnd; i > done; i--)
            insertOrder.push_back(i - 1);

        done = groupEnd; // I put the "done" with where the group end

        // Now go to next jacobsthal (cur + 2x before number)
        std::size_t next = current + (2 * prev); //seq jacob 3, 5, 11, 21 ...
        prev = current;
        current = next;
    }
    return insertOrder;
}

//check if the input was correct
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
    
    // Vector
    std::clock_t start = std::clock();
    std::vector<int> vec;
    for (int i = 1; i < argc; i++)
        vec.push_back(parseNumber(argv[i]));

    vec = sortInput(vec);
    std::clock_t end = std::clock();
    double vecTime = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000000;
    
    // deque
    start = std::clock();
    std::deque<int> deq;
    for (int i = 1; i < argc; i++)
        deq.push_back(parseNumber(argv[i]));
    deq = sortInput(deq);
    end = std::clock();
    double deqTime = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000000;

    std::cout << "Before:";
    for (int i = 1; i < argc; i++)
        std::cout << " " << argv[i];
    std::cout << "\nAfter:";
    for (size_t i = 0; i < vec.size(); i++)
        std::cout << " " << vec[i];

    std::cout << "\nTime to process a range of " << vec.size()
            << " elements with std::vector : " << vecTime
            << " us" << std::endl;

    std::cout << "Time to process a range of " << deq.size()
            << " elements with std::deque : " << deqTime
            << " us" << std::endl;
}

template <typename Container>
Container PmergeMe::sortInput(Container cont)
{
    if (cont.size() < 2)
        return cont;

    bool isOdd = (cont.size() % 2 != 0); // to check if is odd or pair
    Container leftover;
    if (isOdd)
    {
        // retire last number and save if is odd, to have only pairs
        leftover.push_back(cont.back());
        cont.pop_back();
    }

    std::vector<std::pair<int, int> > pair;
    for(size_t i = 0; i < cont.size(); i+=2)
    {
        if (cont[i] > cont[i + 1])
            pair.push_back(std::make_pair(cont[i], cont[i + 1]));
        else
            pair.push_back(std::make_pair(cont[i + 1], cont[i]));
    }

    // to put only High numbers
    Container high;

    for (size_t i = 0; i < pair.size(); i++)
        high.push_back(pair[i].first);

    // to sort the highs
    high = sortInput(high);

    Container low;
    std::vector<bool> wasUsed(pair.size(), false);

    for (size_t i = 0; i < high.size(); i++)
    {
        for (size_t j = 0; j < pair.size(); j++)
        {
            //pair not used and it belongs to high[i]
            if (!wasUsed[j] && pair[j].first == high[i])
            {
                low.push_back(pair[j].second);
                wasUsed[j] = true;
                break; // find pair and put "true" and skip to next number
            }
        }
    }

    if (isOdd)
        low.push_back(leftover[0]);

    Container mainChain(high);
    mainChain.insert(mainChain.begin(), low[0]);

    // put count of numbers in the container of "low", [392, 112, 201] == 3
    // get the order (indexes of low) to insert the lows
    // low.size() = 6 -> [2, 1, 4, 3, 5] low[0] was already in the mainChain

    std::vector<std::size_t> insertOrder = jacobsthalNumbers(low.size());

    for (std::size_t i = 0; i < insertOrder.size(); i++)
    {
        std::size_t pos = insertOrder[i];   // what number insert now? the index (e.g 4)
        int value = low[pos];         // the number from index (e.g 291)
    
        // default I put the end from mainChain to search
        typename Container::iterator limit = mainChain.end();
    
        // if the index was low compare to size
        // search the number from high, because I dont need to pass
        // because the number from low, was under high
        if (pos < high.size())
            limit = std::find(mainChain.begin(), mainChain.end(), high[pos]);
    
        // binary search between begin and the limit and return the pos to put value
        // after the smaller numbers and before the bigger number
        typename Container::iterator where = std::lower_bound(mainChain.begin(), limit, value);
    
        // insert the number
        mainChain.insert(where, value);
    }
    return mainChain;
}


/*
std::vector<int> PmergeMe::sortVector(std::vector<int> vec)
{
    if (vec.size() < 2)
        return vec;

    bool isOdd = (vec.size() % 2 != 0); // to check if is odd or pair
    std::vector<int> leftover;
    if (isOdd)
    {
        // retire last number and save if is odd, to have only pairs
        leftover.push_back(vec.back());
        vec.pop_back();
    }

    std::vector<std::pair<int, int> > pair;
    for(size_t i = 0; i < vec.size(); i+=2)
    {
        if (vec[i] > vec[i + 1])
            pair.push_back(std::make_pair(vec[i], vec[i + 1]));
        else
            pair.push_back(std::make_pair(vec[i + 1], vec[i]));
    }

    // to put only High numbers
    std::vector<int> high;

    for (size_t i = 0; i < pair.size(); i++)
        high.push_back(pair[i].first);

    // to sort the highs
    high = sortVector(high);

    std::vector<int> low;
    std::vector<bool> wasUsed(pair.size(), false);

    for (size_t i = 0; i < high.size(); i++)
    {
        for (size_t j = 0; j < pair.size(); j++)
        {
            //pair not used and it belongs to high[i]
            if (!wasUsed[j] && pair[j].first == high[i])
            {
                low.push_back(pair[j].second);
                wasUsed[j] = true;
                break; // find pair and put "true" and skip to next number
            }
        }
    }

    if (isOdd)
        low.push_back(leftover[0]);

    std::vector<int> mainChain(high);
    mainChain.insert(mainChain.begin(), low[0]);

    // put count of numbers in the container of "low", [392, 112, 201] == 3
    // get the order (indexes of low) to insert the lows
    // low.size() = 6 -> [2, 1, 4, 3, 5] low[0] was already in the mainChain

    std::vector<std::size_t> insertOrder = jacobsthalNumbers(low.size());

    for (std::size_t i = 0; i < insertOrder.size(); i++)
    {
        std::size_t pos = insertOrder[i];   // what number insert now? the index (e.g 4)
        int value = low[pos];         // the number from index (e.g 291)

        // default I put the end from mainChain to search
        std::vector<int>::iterator limit = mainChain.end();

        // if the index was low compare to size
        // search the number from high, because I dont need to pass
        // because the number from low, was under high
        if (pos < high.size())
            limit = std::find(mainChain.begin(), mainChain.end(), high[pos]);

        // binary search between begin and the limit and return the pos to put value
        // after the smaller numbers and before the bigger number
        std::vector<int>::iterator where = std::lower_bound(mainChain.begin(), limit, value);

        // insert the number
        mainChain.insert(where, value);
    }
    return mainChain;
}
*/
