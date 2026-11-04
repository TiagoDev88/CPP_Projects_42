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
        std::cout << argv[i][0];

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
    
    for (size_t i = 0; i < _input.size(); i++)
    {
        std::cout << _input[i] << ", " << std::endl;
    }

    for (size_t i = 0; i < _vec.size(); i++)
    {
        std::cout << "vector " << _vec[i] << ", " << std::endl;
    }
    
}

// Merge-Insertion Sort ==  Ford-Johnson

std::vector<int> PmergeMe::sortVector(std::vector<int>& vec)
{
    std::vector<int> high;

    //fazer verificacao se e impar ou nao.
    if (vec.size() < 2)
        return vec;

    for (size_t i = 0; i < vec.size(); i++)
    {
        std::cout << "vector " << vec[i] << " with address " << &vec[i] << ", " << std::endl;
    }

    std::vector<std::pair<int, int>> pair;
    for(size_t i = 0; i < vec.size(); i+=2)
    {
        if (vec[i] > vec[i + 1])
        {
            pair.push_back(std::make_pair(vec[i], vec[i + 1]));
            high.push_back(vec[i]);
            // low.push_back(vec[i + 1]);
        }
        else
        {
            pair.push_back(std::make_pair(vec[i + 1], vec[i]));
            high.push_back(vec[i + 1]);
            // low.push_back(vec[i]);
        }
    }
    
    // for (size_t i = 0; i < pair.size(); i++)
    //     high.push_back(pair[i].first);
    std::vector<int> principal = sortVector(high);
    // _vec.insert(_vec.end(), high.begin(), high.end());
    // principal.insert(principal.begin(), );
    return principal;
}

std::deque<int> PmergeMe::sortDeque(std::deque<int>& deq)
{
    
}