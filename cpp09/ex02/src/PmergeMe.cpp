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

void PmergeMe::run(int argc, char** argv)
{
    int i = 1;
    while (i < argc)
    {
        std::cout << argv[i] << " ,";

        if (std::isdigit(argv[i][0]))
        {
            _input.push_back(std::stoi(std::string(argv[i])));
        }
        else
            std::cout << "Nao e digito nem espaco\n";
        i++;
    }
    _vec = sortVector(_input);
    
    std::cout << std::endl;

    for (size_t i = 0; i < _vec.size(); i++)
    {
        std::cout << "vector " << _vec[i] << ", " << std::endl;
    }
    
}

// Merge-Insertion Sort ==  Ford-Johnson

std::vector<int> PmergeMe::sortVector(std::vector<int>& vec)
{
    //fazer verificacao se e impar ou nao.
    if (vec.size() < 2)
        return vec;

    bool impar = (vec.size() % 2 != 0);
    std::vector<int> imp;
    if (impar)
    {
        std::cout << "entrou no impar\n";
        imp.push_back(vec.back());
        vec.pop_back();
    }
    std::vector<std::pair<int, int>> pair;
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

    std::vector<int> low;
    for (size_t i = 0; i < high.size(); i++)
    {
        for (size_t j = 0; j < pair.size(); j++)
        {
            if (pair[j].first == high[i])
                low.push_back(pair[j].second);
            break;
        }
    }
    std::cout << std::endl;

    for (size_t i = 0; i < high.size(); i++)
    {
        std::cout << "high " << high[i] << ", " << std::endl;
    }

    for (size_t i = 0; i < low.size(); i++)
    {
        std::cout << "low " << low[i] << ", " << std::endl;
    }
    std::vector<int> principal(high);
    // _vec.insert(_vec.end(), high.begin(), high.end());
    // principal.insert(principal.begin(), );
    return principal;
}

std::deque<int> PmergeMe::sortDeque(std::deque<int>& deq)
{
    
}